#include "s21_decimal.h"

void divide_decimal_by_10(s21_decimal *src) {
  int carry = 0;
  int binary_array[96] = {0};
  int result[96] = {0};
  convert_decimal_to_bits(*src, binary_array);
  for (int i = 95; i >= 0; i--) {
    int current_sum = (carry << 1) + binary_array[i];
    result[i] = current_sum / 10;
    carry = current_sum % 10;
  }
  for (int j = 95; j >= 0; j--) {
    if (result[j])
      set_1_bit(&src->bits[j / 32], j % 32);
    else
      set_0_bit(&src->bits[j / 32], j % 32);
  }
}

int s21_negate(s21_decimal src, s21_decimal *res) {
  int result = OK;
  if (!res) {
    result = ERR;  // Проверка наличия корректного указателя на результат.
  } else {
    set_zero(res);  // Инициализация результата нулем.
    set_scale(res, get_scale(src));  // Установка масштаба результата,
                                     // соответствующего исходному числу.

    // Определение знака исходного числа и установка соответствующего бита знака
    // в результате.
    if (get_bit(src, SIGN_POS) == 0) {
      set_bit(res, SIGN_POS);
    } else {
      set_null(res, SIGN_POS);
    }

    // Итерация через каждый бит исходного числа и копирование его дополнения в
    // результат.
    for (size_t pos = 0; pos < 96; pos++) {
      if (get_bit(src, pos) == 0) {
        set_null(res, pos);
      } else {
        set_bit(res, pos);
      }
    }
  }
  return result;  // Возврат успешного завершения.
}

// Функция для округления десятичного числа.
int s21_round(s21_decimal src, s21_decimal *res) {
  int result = OK;
  if (!res)
    result = ERR;  // Проверка наличия корректного указателя на результат.
  else {
    set_zero(res);  // Инициализация результата нулем.
    if (get_scale(src) == 0) {
      *res = src;
      // Если у исходного числа нет дробной части, скопировать его в результат.
    } else {
      int sign = get_sign(&src);  // Получение знака исходного числа.
      set_null(&src, SIGN_POS);  // Удаление бита знака из исходного числа.

      s21_decimal temp_val_int = {{0}};
      // Инициализация временного десятичного числа для целой части.
      s21_decimal temp_val_fract = {{0}};
      // Инициализация временного десятичного числа для дробной части.
      s21_decimal one = {{1, 0, 0, 0}};  // Десятичное представление числа 1.

      s21_truncate(src, &temp_val_int);
      // Извлечение целой части из исходного числа.
      s21_sub(src, temp_val_int, &temp_val_fract);  // Вычисление дробной части.
      set_scale(&temp_val_fract, get_scale(temp_val_fract) - 1);
      // Изменение масштаба.
      *res = temp_val_int;  // Копирование целой части в результат.
      s21_decimal cpy_temp_val_fract = temp_val_fract;
      int last_numb = 0;
      while (cpy_temp_val_fract.bits[0] > 0) {
        last_numb = cpy_temp_val_fract.bits[0];
        divide_decimal_by_10(&cpy_temp_val_fract);
      }
      int scale = get_scale(temp_val_fract);
      // Если округленная дробь равна или больше 0.5, добавить 1 к целой части.
      if ((((scale > 5)) && last_numb > 5) ||
          (last_numb == 5 &&
           (scale > 0 || test_bit(temp_val_int.bits[0], 0))) ||
          (last_numb > 5 && scale == 0))
        s21_add(temp_val_int, one, res);
      if (sign) set_bit(res, SIGN_POS);
      // Восстановление бита знака при необходимости.
    }
  }
  return result;  // Возврат успешного завершения.
}

// Функция для усечения десятичного числа.
int s21_truncate(s21_decimal src, s21_decimal *res) {
  int result = OK;
  if (src.bits[2] == S21_MAX_UINT && src.bits[1] == S21_MAX_UINT &&
      src.bits[0] == S21_MAX_UINT && !get_scale(src))
    result = ERR;  // Проверка наличия корректного указателя на результат.
  int exp = get_scale(src);
  for (; exp > 0; exp--) {
    divide_decimal_by_10(&src);
  }
  set_exponent(0, &src);
  *res = src;
  return result;  // Возврат успешного завершения.
}

// Функция для вычисления наименьшего целого числа, не большего данного
// десятичного числа.
int s21_floor(s21_decimal src, s21_decimal *res) {
  int result = OK;
  if (!res)
    result = ERR;  // Проверка наличия корректного указателя на результат.
  else {
    set_zero(res);  // Инициализация результата нулем.
    int sign = get_sign(&src);  // Получение знака исходного числа.
    s21_decimal one = {{1, 0, 0, 0}};  // Десятичное представление числа 1.
    s21_decimal val_tmp = {{0}};  // Инициализация временного десятичного числа.

    s21_truncate(
        src, &val_tmp);  // Усечение исходного числа для получения целой части.

    // Вычитание 1 из усеченного значения, если исходное число отрицательное.
    if (sign)
      s21_sub(val_tmp, one, res);
    else
      *res = val_tmp;
  }
  return result;  // Возврат успешного завершения.
}
