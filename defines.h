#ifndef DEFINES_H
#define DEFINES_H

/**     Каскады */
#define FD_FACE_CASCADE_PATH "/users/dankulakovich/rec/resources/cascades/face.xml"
#define FD_SMILE_CASCADE_PATH "/users/dankulakovich/rec/resources/cascades/smile.xml"
#define FD_EYES_CASCADE_PATH "/users/dankulakovich/rec/resources/cascades/eyes.xml"

/**     Детектор лиц */
#define FD_SCALE_FACTOR 1.05
#define FD_MIN_NEIGHBOURS 30
#define FD_MIN_SIZE_RATIO 0.1
#define FD_MAX_SIZE_RATIO 0.5

/**     LBPH Распознование лиц (по гистограммам): */
#define LBPH_RADIUS 3
#define LBPH_NEIGHBORS 8
#define LBPH_GRID_X 8
#define LBPH_GRID_Y 8
#define LBPH_THRESHOLD 180.

/**     Тестовые данные */
#define TEST_1_PATH "/users/dankulakovich/rec/resources/test/12.jpeg"
#define TEST_2_PATH "/users/dankulakovich/rec/resources/test/13.jpeg"
#define TEST_3_PATH "/users/dankulakovich/rec/resources/test/me.jpg"
#define TEST_4_PATH "/users/dankulakovich/rec/resources/test/IMG_0255.JPG"

/**     Датасеты */
#define DATASET_ID_PATH "/users/dankulakovich/rec/resources/dataset/id_"
#define DATASET_PATH "/users/dankulakovich/rec/resources/dataset/"

/**     Модели */
#define MODELS_PATH "/users/dankulakovich/rec/resources/models/"
#define MODEL_FILE "/users/dankulakovich/rec/resources/models/model.yml"

/**     Текст справки */
#define TEXT_INFO "\t\t\t\tСПРАВКА\n\n1. Нахождение любых лиц на изображении.\n    Чтобы найти любые лица на фотографии, необходимо сначала загрузить\n    изображение, а после нажать на кнопку 'Найти лица'\n\n2. Определение конкретного лица на фотографии.\n    Чтобы найти конкретное лицо на фотографии, необходимо сначала добавить\n    датасет с этим человеком путем загрузки его фотографий в папку с его\n    датасетом,  либо нажать на кнопку 'Добавить датасет', тогда вас\n    попросят ввести имя человека на латинице и программа включит камеру\n    для взятия 20 кадров и запишет их в папку датасета. Когда датасет добавлен,\n    нажмите на кнопку 'Обучить модель', тогда программа предложит взять\n    заранее обученную модель, если она существует, или обучить модель заново.\n    Затем нажмите на кнопку 'Узнать кто это', и тогда программа отрисует лицо\n    при совпадении с моделью, иначе напишет 'Match not found'\n\n3. Сохранение обработанного изображения.\n    Сохранить модель можно, нажав на кнопку 'Сохранить' и указав\n    путь сохранения"

#endif // DEFINES_H
