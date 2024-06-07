#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  // Обнуление переменной result
  memset(&(result->bits), 0, sizeof(result->bits));
  // Вычисление показателей степени для чисел value_1 и value_2
  int exp_1 = exp_decimal_bin2dec(value_1);
  int exp_2 = exp_decimal_bin2dec(value_2);
  // Выполнение операции сложения с плавающей точкой
  int error = add_main(value_1, exp_1, value_2, exp_2, result);
  return error;  // Возвращаем код ошибки
}

int add_main(s21_decimal value_1, int exp_1, s21_decimal value_2, int exp_2,
             s21_decimal *result) {
  int res = 0, index = 0, sign_index = 0;  // Индекс для определения знаков
                                           // Получение знаковых индексов
  sign_index = get_signs(value_1, value_2, sign_index);
  int greater = -1;  // Переменная для определения, какое значение больше
  // Определение, какое значение больше
  if (sign_index == 3 || sign_index == 4)
    greater = s21_is_greater_num(value_1, value_2, greater);
  int value_1_arr[NUM_255];  // Массив для представления value_1 в виде битов
  int value_2_arr[NUM_255];  // Массив для представления value_2 в виде битов
  int result_arr[NUM_255];  // Массив для представления результата в виде битов
  // Преобразование значений в массивы битов
  to_bit_arrays(value_1, value_2, value_1_arr, value_2_arr, result_arr);
  // Выполнение сложения/умножения
  int error = add_mul_1010(value_1_arr, value_2_arr, &exp_1, &exp_2);
  if (error == 123 && sign_index == 1) {
    res = 1;  // Обработка ошибки, если знак равен 1
  } else if (error == 123 && sign_index == 2) {
    res = 2;
  } else {
    // Обработка ошибки, если знак равен 2
    int count_bit_1 = 0, count_bit_2 = 0;  // Количество битов в value_1 2
    int count_bit = 0;             // Общее количество битов
    int index_1 = 0, index_2 = 0;  // Индекс для перебора value_2_arr 2
    // Вычисление общего количества битов
    count_bit = count_bits(value_1_arr, value_2_arr, &count_bit_1, &count_bit_2,
                           count_bit, &index_1, &index_2);
    if (exp_1 == exp_2 && (sign_index == 1 || sign_index == 2)) {
      // Выполнение операции сложения
      count_bit = perform_addition(value_1_arr, value_2_arr, result_arr,
                                   count_bit, &index);
    } else if (exp_1 == exp_2 && (sign_index == 3 || sign_index == 4))
      // Выполнение операции вычитания
      perform_subtraction(value_1_arr, value_2_arr, result_arr, count_bit,
                          greater, &index);
    // Округление и проверка результата
    round_and_check(result_arr, exp_1, count_bit, &error, &index_1, &index_2);
    exp_1 = index_2;
    if (error == 123 && sign_index == 1) {  // Проверка ошибок и знаков
      res = 1;  // Ошибка с положительным знаком
    } else if (error == 123 && sign_index == 2)
      res = 2;  // Ошибка с отрицательным знаком
    else {
      // Запись результата в формате числа с плавающей запятой
      write_float_decimal_exp_more(result_arr, result, index, 2);
      set_exponent(exp_1, result);  // Установка показателя степени
      set_sign(sign_index, result_arr, result, greater);  // Установка знака
      res = 0;  // Возврат успешного результата
    }
  }
  return res;
}
