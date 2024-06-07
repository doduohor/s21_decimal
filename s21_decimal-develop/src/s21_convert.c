#include "s21_decimal.h"

// Функция для перевода переменной src из типа s21_decimal в тип float
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  double result = 0;  // Переменная для хранения промежуточного результата
  int off = 0;  // Переменная для хранения смещения десятичной точки
  // Проходим по каждому биту числа src
  for (int i = 0; i < 96; i++) {
    // Если i-ый бит равен 1, то добавляем соответствующее ему значение в
    // результат
    int shift = i % 32;
    if ((src.bits[i / 32] & (1U << shift)) != 0) {
      result += pow(2, i);
    }
  }
  // Если есть смещение десятичной точки
  if ((off = (src.bits[3] & ~0x80000000) >> 16) > 0) {
    // Делим результат на 10 в степени off, чтобы вернуть десятичную точку на
    // своё место
    for (int i = off; i > 0; i--) {
      result /= 10.0;
    }
  }
  // Присваиваем значение результата переменной dst
  *dst = (float)result;
  // Если знак числа отрицательный, то умножаем результат на -1
  *dst *= src.bits[3] >> 31 ? -1 : 1;
  return 0;  // Возвращаем код успешного выполнения функции
}

// Функция для преобразования числа в формате s21_decimal в целое число
int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = 0;  // Переменная для отслеживания ошибок
  int count_bit = 0;  // Количество битов в числе
  int value_1_arr[NUM_255];  // Массив для хранения значений битов числа
  initialize_value_1_arr(value_1_arr);  // Инициализируем массив value_1_arr
  convert_decimal_to_bits(src, value_1_arr);
  // Преобразуем число из формата s21_decimal в битовую форму
  count_bit =
      calculate_count_bit(value_1_arr);  // Вычисляем количество битов числа
  int exp_1 = exp_decimal_bin2dec(
      src);  // Получаем показатель степени числа в десятичном формате
  if (count_bit > 32 && exp_1 > 0 && exp_1 <= 28) {
    // Если количество битов больше 32 и показатель степени в диапазоне от 1 до
    // 28
    error = divide_by_10(value_1_arr, &exp_1,
                         &count_bit);  // Делим число на 10 и обновляем
                                       // показатель степени и количество битов
    if (!error) {
      *dst = convert_bits_to_int(
          value_1_arr,
          count_bit);  // Преобразуем битовое представление числа в целое число
      if (test_bit(src.bits[3], 31)) {
        *dst *= -1;  // Если число отрицательное, меняем знак результирующего
                     // целого числа
      }
    }
  } else {
    error = check_bits(src);  // Проверяем биты числа на ошибки
    if (!error) {
      *dst = convert_bits_to_int(
          value_1_arr,
          count_bit);  // Преобразуем битовое представление числа в целое число
      if (test_bit(src.bits[3], 31)) {
        *dst *= -1;  // Если число отрицательное, меняем знак результирующего
                     // целого числа
      }
      *dst /= (int)pow(
          10,
          exp_decimal_bin2dec(src));  // Делим целое число на 10 в степени exp_1
    }
  }
  return error;  // Возвращаем код ошибки
}

// Функция для преобразования числа с плавающей точкой в s21_decimal формат
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int res = 0;
  if (dst && !is_inf(src) && !is_nan(src)) {
    bool flag_minus = FALSE;  // Флаг для отслеживания отрицательного значения
    // Проверяем, что указатель на dst не является нулевым и src
    // не является бесконечностью (inf) или не числом (NaN)
    set_zero(dst);  // Обнуляем значение в dst
    if (src < 0) src *= -1.0f, flag_minus = TRUE;
    // Если src отрицательное, умножаем его на -1 и
    // устанавливаем флаг_minus в TRUE
    float fl_int = 0.0;                    // Целая часть числа
    float fl_fract = modff(src, &fl_int);  // Дробная часть числа
    int whole = s21_from_float_string((int)fl_int, fl_fract, dst);
    // Преобразуем целую и дробную части в s21_decimal формат
    int scale_temp = get_scale(*dst);  // Сохраняем текущий масштаб числа
    s21_from_int_to_decimal(whole, dst);
    // Преобразуем целую часть в s21_decimal формат
    set_scale(dst, scale_temp);  // Восстанавливаем масштаб числа
    if (flag_minus) set_bit(dst, SIGN_POS);
    // Если значение было отрицательным, устанавливаем соответствующий бит в dst
  } else {
    set_zero(dst);  // Обнуляем значение в dst
    res = 1;        // Возвращаем 1 в случае ошибки
  }
  return res;  // Возвращаем 0 в случае успешного преобразования
}

// Функция для преобразования целого числа в s21_decimal формат
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int res = 0;
  // Проверяем, что указатель на dst не является нулевым
  if (!dst)
    res = 1;
  else {
    memset(&(dst->bits), 0, sizeof(dst->bits));  // Обнуляем биты значения dst
    if (src < 0) set_bit(dst, SIGN_POS), src = -src;
    // Если src отрицательное, устанавливаем соответствующий
    // бит в dst и меняем знак src на положительный
    dst->bits[0] = src;
    // Присваиваем значение src нулевому элементу массива bits в dst
  }
  return res;  // Возвращаем 0 в случае успешного преобразования
}
