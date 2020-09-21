// Настройки главной светодиодной ленты
constexpr uint8_t LIGHT_STRIP_PIN = 6;				  // Пин, к которому подключена главная лента
constexpr uint8_t LIGHT_STRIP_LED_COUNT = 144;		  // Количество светодиодов во всей главной ленте
constexpr uint8_t LIGHT_STRIP_BRIGHTNESS = 50;		  // Яркость ленты. Диапазон: 0 - 255
constexpr uint8_t LIGHT_STRIP_ANIMATION_MODIFIER = 2; // Модификатор для определения скорости ленты
constexpr uint8_t LIGHT_STRIP_ANIMATION_STEP = 2;	  // Шаг радуги. Чем больше, тем меньше
constexpr uint8_t LIGHT_STRIP_ANIMATION_MODE = 2;	  // Тип анимации. https://github.com/GGorAA/EUCLight/wiki/Animation-modes что бы узнать более

// Настройки стоп-сигнала
// Пины
constexpr uint8_t BRAKELIGHT_PIN = 5; // Пин подключения адресной ленты для стоп-сигнала
// Свет
constexpr uint8_t BRAKELIGHT_BRIGHTNESS_ON = 255;  // Яркость включенного стоп-сигнала. Диапазон: 0 - 255
constexpr uint8_t BRAKELIGHT_BRIGHTNESS_IDLE = 40; // Яркость бездейвствующего стоп-сигнала. Диапазон: 0 - 255
// Другое
constexpr uint8_t BRAKELIGHT_MATRIX_HEIGHT = 3;													   // Высота "матрицы" стоп-сигнала
constexpr uint8_t BRAKELIGHT_MATRIX_WIDTH = 8;													   // Ширина "матрицы" стоп-сигнала
constexpr uint8_t BRAKELIGHT_MATRIX_LEDCOUNT = BRAKELIGHT_MATRIX_WIDTH * BRAKELIGHT_MATRIX_HEIGHT; // Количество светодиодов в каждом отрезке. Пишеться в порядке сверху-вниз
constexpr uint8_t BRAKELIGHT_SENSITIVITY = -5;													   // Чувствительность стоп-сигнала. Чем ближе к нулю, тем чувствительнее

#define DEVICE_MODEL GotwayMcm2 // Модель моноколеса. Смотреть https://github.com/GGorAA/EUCLight для просмотра всех сущевствующих имен