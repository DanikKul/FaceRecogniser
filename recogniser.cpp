#include "recogniser.h"
#include <opencv2/face.hpp>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <sys/stat.h>
#include <QMessageBox>
#include <fstream>
#include "defines.h"
#include "recogniserdrawer.h"
#include "exceptions.h"

// Конструктор

Recogniser::Recogniser() {

    // Загрузка каскада Хаара
    std::cout << "INFO: Загрузка каскада Хаара..." << std::endl;
    std::cout << FD_FACE_CASCADE_PATH << std::endl;

    try {
        this->classifier.load(FD_FACE_CASCADE_PATH);
        if (this->classifier.empty()) throw ExceptionEmpty();
        std::cout << "SUCCESS: Выполнена загрузка каскада Хаара!" << std::endl;
    } catch (ExceptionEmpty& exception) {
        std::cout << "ERROR: Файл не был загружен!" << std::endl;
    }

    // Инициализация указателя на LBPHFaceRecogniser (Local Binary Patterns Histograms)
    // Гистограммы локальных бинарных шаблонов

    // Параметры для LBPH алгоритма

    // 1. Радиус, используемый для построения кругового локального бинарного шаблона.
    // Чем больше радиус, тем более плавным будет изображение,
    // но при этом вы сможете получить больше пространственной информации.

    // 2. Количество точек выборки для построения кругового локального двоичного шаблона.
    // Подходящим значением является использование 8 точек выборки.
    // Чем больше точек выборки вы включаете, тем выше вычислительные затраты.

    // 3. Количество ячеек в горизонтальном направлении,
    // 8 - это распространенное значение, используемое в публикациях.
    // Чем больше ячеек, чем тоньше сетка, тем выше размерность результирующего вектора объектов.

    // 4. Тоже самое, что и 3 параметр, но в вертикальном направлении.

    // 5. Пороговое значение, применяемое при прогнозировании.
    // Если расстояние до ближайшего соседа больше порогового значения,
    // этот метод возвращает значение -1.

    std::cout << "INFO: Инициализация LBPHFaceReconizer..." << std::endl;
    this->model = cv::face::LBPHFaceRecognizer::create(1, 8, 8, 8, 50);
    std::cout << "SUCCESS: Выполнена инициализация LBPHFaceRecognizer!" << std::endl;
}

// Деструктор

Recogniser::~Recogniser() = default;

// Обработка фотографий для обучения модели

int Recogniser::extractFaces(cv::Mat &img, cv::Mat &face) {

    // Инициализация матрицы

    cv::Mat img_gray;

    // Конвертация изображения из BGR в Gray (из 3-х канального изображения в 1-о канальное)

    try {

        if (img.channels() != 3) throw ExceptionWrongChannels();
        cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);

    } catch (ExceptionWrongChannels& exception) {
        exception.getError();
        return 0;
    } catch (...) {
        Exception exception;
        exception.getError();
        return 0;
    }

    // Нахождение лиц по каскаду Хаара и запись координат в faces

    std::vector<cv::Rect> faces;
    classifier.detectMultiScale(img, faces, 1.1, 25);

    // Принять к сведению, что алгоритм корректно работает при одном лице на фотографии,
    // иначе функция пропустит изображение и вернет 0!

    if (faces.size() > 0) {
        face = img_gray(faces[0]);
        return 1;
    } else
        return 0;
}

// Возвращает координаты лица

int Recogniser::extractRect(cv::Mat &img, cv::Mat &face, std::vector<cv::Rect>& faces) {

    // Инициализация матрицы

    cv::Mat img_gray;

    // Конвертация изображения из BGR в Gray (из 3-х канального изображения в 1-о канальное)

    try {

        if (img.channels() != 3) throw ExceptionWrongChannels();
        cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);

    } catch (ExceptionWrongChannels& exception) {
        exception.getError();
        return 0;
    } catch (...) {
        Exception exception;
        exception.getError();
        return 0;
    }

    // Нахождение лиц по каскаду Хаара и запись координат в faces

    classifier.detectMultiScale(img, faces, 1.1, 25);

    // Принять к сведению, что алгоритм корректно работает при одном лице на фотографии,
    // иначе функция пропустит изображение и вернет 0!

    if (faces.size() > 0) {
        face = img_gray(faces[0]);
        return 1;
    } else
        return 0;
}

// Проверка на существование директории

bool Recogniser::existDir(const StringConv name) {
    struct stat s{};
    try {
        if (stat(name.c_str(), &s)) throw ExceptionDirectory();
    } catch (ExceptionDirectory& exception) {
        exception.getError();
        return false;
    } catch (...) {
        Exception exception;
        exception.getError();
        return false;
    }
    return S_ISDIR(s.st_mode);
}

// Получение датасета с фотографиями с помощью камеры и запись в папку

void Recogniser::getImages(const StringConv dirname) {

    // Стандартный путь к датасету

    std::string path_output = DATASET_ID_PATH;

    // ID объекта (в данном случае конкретного лица)

    std::string id(dirname.c_str());
    std::string extension = ".jpg";

    std::set<std::filesystem::path> paths;
    for (const auto &file : std::filesystem::directory_iterator(DATASET_PATH)) if (file.path().filename().c_str()[0] != '.') paths.insert(file.path());

    int last_id = paths.size();

    path_output += std::to_string(last_id) + "_" + id + "/";
    std::cout << path_output << std::endl;

    // Если папка существует - прекратить выполнение функции

    if (existDir(path_output.c_str())) {
        std::cout << "ERROR: Папка уже существует" << std::endl;
        return;
    }

    // Создание папки для датасета

    mkdir(path_output.c_str(), 0777);

    // Инициализация захвата камеры ноутбука и запись 20 кадров с камеры в папку датасета

    cv::VideoCapture capture;
    try {
        capture.open(0, cv::CAP_AVFOUNDATION);
        if (!capture.isOpened()) throw ExceptionCamera();
    } catch (ExceptionCamera& exception) {
        exception.getError();
        return;
    } catch (...) {
        Exception exception;
        exception.getError();
        return;
    }

    for (int i = 1; i <= 20; i++) {
        cv::Mat img;

        try {

            // Чтение кадра

            if (!capture.read(img)) throw ExceptionCameraRead();

            // Запись кадра в папку

            if (!imwrite(path_output + std::to_string(i) + extension, img)) throw ExceptionFileWrite();

        } catch (ExceptionCameraRead& exception) {
            exception.getError();
            continue;
        } catch (ExceptionFileWrite& exception) {
            exception.getError();
            continue;
        } catch (...) {
            Exception exception;
            exception.getError();
            continue;
        }

        // Ожидание 30 мс

        cv::waitKey(30);
    }
    capture.release();
}

// Обучение модели

void Recogniser::train(const StringConv& in_dir) {

    // Проверка существует ли сохраненная модель

    QMessageBox::StandardButton reply;
    std::ifstream file(MODEL_FILE);
    if (!file) reply = QMessageBox::Yes;
    else reply = QMessageBox::question(0, "", "Вы хотите переобучить модель?", QMessageBox::Yes | QMessageBox::No);

    // Если нет модели или если пользователь захотел переобучить модель

    if (reply == QMessageBox::Yes) {
        std::cout << "INFO: Начинается обучение по датасетам..." << std::endl;
        std::vector<int> faceIds;
        std::vector<cv::Mat> faceSamples;

        // Создание множества с именами объектов

        std::set<std::filesystem::path> paths;
        for (const auto &file : std::filesystem::directory_iterator(in_dir.cpp_str())) if (file.path().filename().c_str()[0] != '.') paths.insert(file.path());

        // Проход по файлам датасетов (поскольку пути уникальны, их можно записать в множество)
        // тем самым избавившись от сортировки
        for (const auto& file : paths) std::cout << file.filename() << std::endl;
        for (const auto& file : paths) {
            std::string label = file.filename();
            std::string num;
            std::cout << "INFO: Изображения в директории: " << label << "...\n";

            // Формат директорий - id_0_<name1>, id_1_<name2>...

            for (int i = 3; label[i] != '_'; i++) num.push_back(label[i]);
            int faceID = std::stoi(num);

            // Проход по файлам (фотографиям датасета)

            for (const auto &f : std::filesystem::directory_iterator(file)) {
                cv::Mat src, face;
                std::cout << f.path() << "\n";

                // Чтение файла по данному пути

                try {
                    src = cv::imread(f.path());
                    if (src.empty()) throw ExceptionEmpty();
                } catch (ExceptionEmpty& exception) {
                    exception.getError();
                    continue;
                } catch (...) {
                    Exception exception;
                    exception.getError();
                    continue;
                }

                // Извлечение лица из фотографии и их занесение в вектор обработанных матриц + запись id

                if (extractFaces(src, face)) {
                    faceSamples.emplace_back(face);
                    faceIds.emplace_back(faceID);
                }
            }

            // Обучение модели по заданным матрицам и ID

            model->train(faceSamples, faceIds);
            std::cout << "SUCCESS: Выполнена обработка " << file.filename() << std::endl;
        }
        this->writeModel(MODEL_FILE);
        std::cout << "SUCCESS: Обучение по датасетам выполнено!" << std::endl;
    }

    // Если пользователь решил загрузить обученную заранее модель

    else if (reply == QMessageBox::No) {
        std::cout << "INFO: Начинается загрузка обученной модели..." << std::endl;

        try {
            model->read(MODEL_FILE);
            if (model.empty()) throw ExceptionFileLoad();
        } catch (ExceptionFileLoad& exception) {
            exception.getError();
            return;
        } catch (...) {
            Exception exception;
            exception.getError();
            return;
        }

        std::cout << "SUCCESS: Загрузка модели завершена" << std::endl;
    }
}

// Распознание конкретных лиц по обученной модели

void Recogniser::recognize(cv::Mat& img, const StringConv& dataset_dir) {
    std::cout << "INFO: Процесс распознавания конкретных лиц..." << std::endl;

    // Имена объектов должны быть в том же порядке как и в обучении модели
    // поэтому запишем их в множество путей и распарсим

    std::vector<std::string> names;
    std::set<std::filesystem::path> paths;

    for (const auto& file : std::filesystem::directory_iterator(dataset_dir.cpp_str()))
        if (file.path().filename().c_str()[0] != '.')
            paths.insert(file.path().filename());

    for (const auto& file : paths) {
        std::string path = file;
        std::string name;
        int idx = 5;
        int counter = 0;
        while (path[idx] != '\0') counter++, idx++;
        name = path.substr(5, counter);
        names.push_back(name);
        std::cout << name << std::endl;
    }

    // Извлечение лица из изображения

    cv::Mat face;
    std::vector<cv::Rect> faces;
    extractFaces(img, face);
    extractRect(img, face, faces);

    // Предположение о том, что изображено на фотографии
    // predictedLabel -  метод predict запишет в эту переменную номер объекта
    // confidence - чем больше это значение, тем меньше модель уверена,
    // что этот объект является объектом распознавания
    // (значение 0 означает идеальное совпадение)

    int predictedLabel = -1;
    double confidence = 0.0;
    if (!face.empty()) model->predict(face, predictedLabel, confidence);

    // Если нет совпадающего объекта обучения predictedLabel = -1
    // Иначе predictedLabel = x, где x - порядковый номер распознанного объекта

    std::cout << predictedLabel << std::endl;


    // Обработка изображения
    if (predictedLabel != -1) {

        RecogniserDrawer rd(names[predictedLabel].c_str(), cv::Scalar(0, 255, 0), cv::Scalar(255, 0, 0));
        rd.drawFaces(img, faces);
        rd.setTextInImage(img, cv::Point(faces[0].x, faces[0].y - 20));
        rd.setText((std::to_string(100 * (double(200 - confidence) / 200)) + std::string("%") + std::string(" match")).c_str());
        rd.setTextInImage(img, cv::Point(20, img.size().height * 0.9));

        std::cout << "\nPrediction: " << names[predictedLabel]
                  << "\nConfidence: " << confidence << "\n\n" << std::endl;
    } else {

        RecogniserDrawer rd("Match Not Found", cv::Scalar(0, 255, 0), cv::Scalar(255, 0, 0));
        rd.setTextInImage(img, cv::Point(20, img.size().height * 0.9));

        std::cout << "Prediction: Неизвестно модели!" << std::endl;;
    }
    std::cout << "SUCCESS: Процесс распознавания лиц закончен!" << std::endl;
}

void Recogniser::writeModel(const StringConv filename) {

    try {
        if (this->model.empty()) throw ExceptionEmpty();
        this->model->write(filename.c_str());
    } catch (ExceptionEmptyModel& exception) {
        exception.getError();
        std::cout << "ERROR: Запись в файл не осуществлена. Модель пуста!" << std::endl;
        return;
    } catch (...) {
        Exception exception;
        exception.getError();
        return;
    }

}

void Recogniser::load(const StringConv filename) {

    std::ifstream fout(filename.c_str(), std::ios_base::out);
    try {
        fout.open(filename.c_str(), std::ios_base::out);
        if (!fout.is_open()) throw ExceptionFileLoad();
        this->model->read(filename.c_str());
    } catch (ExceptionFileLoad& exception) {
        exception.getError();
        return;
    } catch (...) {
        Exception exception;
        exception.getError();
        return;
    }

    std::cout << "Загружена обученная модель из файла!" << std::endl;

}

bool Recogniser::isEmpty() {
    return this -> classifier.empty() || this -> model.empty();
}
