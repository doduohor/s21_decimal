#include "s21_decimal.h"

// Возвращает значение бита на указанной позиции в числе num
int get_bit(s21_decimal num, int index) {
  unsigned int bit_mask = 1u << (index % 32);
  int bit = ((num.bits[index / 32] & bit_mask) >> (index % 32));
  return bit;
}

// Устанавливает значение бита на указанной позиции в числе
int set_null(s21_decimal *num, int index) {
  unsigned int bit_mask = 1u << (index % 32);
  return num->bits[index / 32] = num->bits[index / 32] & ~bit_mask;
}

void set_zero(s21_decimal *num) {
  memset(&(num->bits), 0, sizeof(num->bits));  // Заполнение битов числа нулями
}

int get_scale(s21_decimal num) {
  int bit_mask = SIGN_POS << 16;  // Маска для извлечения степени
  int scale = (bit_mask & num.bits[3]) >> 16;  // Извлечение степени из числа
  return scale;  // Возвращение значения степени
}

int s21_from_float_string(int whole, float fract, s21_decimal *value) {
  char fr_str[255] = {0};  // Строка для представления дробной части
  char int_str[255] = {0};  // Строка для представления целой части
  int pos = 0;  // Позиция в строке
  int exp = 0;  // Экспонента
  if (fract != 0.0) sprintf(fr_str, "%.9f", fract);
  // Преобразование дробной части в строку
  if (whole != 0.0) sprintf(int_str, "%d", whole);
  // Преобразование целой части в строку
  memmove(fr_str, fr_str + 2, strlen(fr_str));
  // Удаление "0." из строки дробной части
  exp = strlen(int_str);  // Экспонента равна длине целой части
  strcat(int_str, fr_str);  // Объединение целой и дробной частей
  size_t pos_sign_number = strlen(int_str);  // Позиция знака числа
  pos = pos_sign_number;
  if (pos_sign_number > 7 && strlen(fr_str) > 0) {
    while (pos != 7) int_str[pos--] = '\0';  // Усечение числа до 7 цифр
    if ((int)int_str[pos] - '0' > 4) {
      pos--;
      if (int_str[pos] == '9') {
        while (int_str[pos] == '9') int_str[pos--] = '0';  // Инкремент цифры
        int_str[pos]++;
      } else
        int_str[pos]++;
      int_str[7] = '\0';  // Усечение числа до 7 цифр
      pos = strlen(int_str) - 1;
      while (pos >= 0 && int_str[pos] == '0')
        int_str[pos--] = '\0';  // Удаление незначащих нулей
    } else
      while (pos >= 0 && int_str[pos] == '0')
        int_str[pos--] = '\0';  // Удаление незначащих нулей
  }
  exp = (strlen(int_str) - exp);  // Подсчет экспоненты
  set_scale(value, exp);  // Установка масштаба в s21_decimal
  return atoi(int_str);  // Возвращение целочисленного значения строки
}

int take_sign(s21_decimal numb1, s21_decimal numb2) {
  int res_sign = 0;  // Результат определения знаков
  if (!test_bit(numb1.bits[3], 31) && !test_bit(numb2.bits[3], 31))
    res_sign = 1;  // Оба значения положительные (+ и +)
  else if (test_bit(numb1.bits[3], 31) && test_bit(numb2.bits[3], 31))
    res_sign = 2;  // Оба значения отрицательные (- и -)
  else if (!test_bit(numb1.bits[3], 31) && test_bit(numb2.bits[3], 31))
    res_sign = 3;
  // Одно значение положительное, а другое отрицательное (+ и -)
  else
    res_sign = 4;
  // Одно значение отрицательное, а другое положительное (- и +)
  return res_sign;
}

int compare_s21_decimal(const s21_decimal num1, const s21_decimal num2) {
  int result = 0;  // Результат сравнения
  int flag = 0;    // Флаг для прерывания цикла
  for (int i = 3; i >= 0 && !flag; i--) {
    if (num1.bits[i] < num2.bits[i]) {
      result = -1;  // num1 < num2
      flag = 1;  // Установка флага для прерывания цикла
    } else if (num1.bits[i] > num2.bits[i]) {
      result = 1;  // num1 > num2
      flag = 1;  // Установка флага для прерывания цикла
    }
  }
  return result;  // num1 == num2
}

int get_signs(s21_decimal value_1, s21_decimal value_2, int sign_index) {
  if (test_bit(value_1.bits[3], 31) == 0 &&
      test_bit(value_2.bits[3], 31) == 0) {
    // Если бит 31 в поле bits[3] структуры value_1 равен 0
    // И если бит 31 в поле bits[3] структуры value_2 равен 0
    sign_index = 1;  // Устанавливаем значение sign_index в 1
  } else if (test_bit(value_1.bits[3], 31) && test_bit(value_2.bits[3], 31)) {
    // Иначе, если бит 31 в поле bits[3] структуры value_1
    // и бит 31 в поле bits[3] структуры value_2 равны 1
    sign_index = 2;  // Устанавливаем значение sign_index в 2
  } else if (test_bit(value_1.bits[3], 31) == 0 &&
             test_bit(value_2.bits[3], 31)) {
    // Иначе, если бит 31 в поле bits[3] структуры
    // value_1 равен 0 и бит 31 в поле bits[3]
    // структуры value_2 равен 1
    sign_index = 3;  // Устанавливаем значение sign_index в 3
  } else if (test_bit(value_1.bits[3], 31) &&
             test_bit(value_2.bits[3], 31) == 0) {
    // Иначе, если бит 31 в поле bits[3] структуры value_1
    // равен 1 и бит 31 в поле bits[3] структуры value_2
    // равен 0
    sign_index = 4;  // Устанавливаем значение sign_index в 4
  }
  return sign_index;  // Возвращаем значение sign_index
}

void to_bit_arrays(s21_decimal value_1, s21_decimal value_2, int value_1_arr[],
                   int value_2_arr[], int result_arr[]) {
  for (int i = 0; i < NUM_255; i++) {
    result_arr[i] = 2;
    // Инициализируем элементы массива result_arr значением 2
    value_1_arr[i] = 2;
    // Инициализируем элементы массива value_1_arr значением 2
    value_2_arr[i] = 2;
    // Инициализируем элементы массива value_2_arr значением 2
  }
  for (int i = 0; i < 96; i++) {
    // Если бит i в поле bits[i / 32] структуры value_1 равен 1
    if (test_bit(value_1.bits[i / 32], i % 32)) {
      value_1_arr[i] = 1;  // Устанавливаем значение value_1_arr[i] в 1
    } else {
      value_1_arr[i] = 0;  // Иначе, устанавливаем значение value_1_arr[i] в 0
    }
    // Если бит i в поле bits[i / 32] структуры value_2  равен 1
    if (test_bit(value_2.bits[i / 32], i % 32)) {
      value_2_arr[i] = 1;  // Устанавливаем значение value_2_arr[i] в 1
    } else {
      value_2_arr[i] = 0;  // Иначе, устанавливаем значение value_2_arr[i] в 0
    }
  }
}

int count_bits(int value_1_arr[], int value_2_arr[], int *count_bit_1,
               int *count_bit_2, int count_bit, int *index_1, int *index_2) {
  for (int i = 254; i >= 0; i--) {
    if (value_1_arr[i] == 1) *index_1 = 1;
    // Если элемент value_1_arr[i] равен 1, устанавливаем значение *index_1 в 1
    if (value_2_arr[i] == 1) *index_2 = 1;
    // Если элемент value_2_arr[i] равен 1, устанавливаем значение *index_2 в 1
    if (*index_1) (*count_bit_1)++;
    // Если *index_1 равно 1, увеличиваем значение *count_bit_1 на 1
    if (*index_2) (*count_bit_2)++;
    // Если *index_2 равно 1, увеличиваем значение *count_bit_2 на 1
  }
  for (int i = 0; i < NUM_255; i++) {
    if (value_2_arr[i] == 2) value_2_arr[i] = 0;
    // Если элемент value_2_arr[i] равен 2, устанавливаем его значение в 0
    if (value_1_arr[i] == 2) value_1_arr[i] = 0;
    // Если элемент value_1_arr[i] равен 2, устанавливаем его значение в 0
  }
  if (*count_bit_1 > *count_bit_2) {
    count_bit = *count_bit_1;
    // Если *count_bit_1 больше *count_bit_2, присваиваем значение *count_bit_1
    // переменной count_bit
  } else if (*count_bit_1 < *count_bit_2) {
    count_bit = *count_bit_2;
    // Если *count_bit_1 меньше *count_bit_2, присваиваем значение *count_bit_2
    // переменной count_bit
  } else {
    count_bit = *count_bit_1;
    // В противном случае, присваиваем значение *count_bit_1 переменной
    // count_bit
  }
  return count_bit;  // Возвращаем значение count_bit
}

int round_and_check(int result_arr[], int exp_1, int count_bit, int *error,
                    int *index_1, int *index_2) {
  *index_2 = exp_1;  // Присваиваем значение exp_1 переменной *index_2
  if (count_bit > 96) {  // Если значение count_bit больше 96
    while (count_bit > 96) {  // Пока значение count_bit больше 96
      *index_1 = 0;  // Устанавливаем значение *index_1 в 0
      if (!*index_2) {  // Если значение *index_2 равно 0
        count_bit = 0;  // Устанавливаем значение count_bit в 0
        for (int i = 254; i >= 0; i--) {
          if (result_arr[i] == 1)
            *index_1 = 1;  // Если элемент result_arr[i] равен 1, устанавливаем
                           // значение *index_1 в 1
          if (*index_1)
            count_bit++;  // Если *index_1 равно 1, увеличиваем значение
                          // count_bit на 1
        }
        if (count_bit > 96) {
          *error = 123;  // Присваиваем значение 123 переменной *error
          break;  // Прерываем цикл
        }
      }
      add_div_10(result_arr, &exp_1, &count_bit);
      // Выполняем функцию add_div_10 с аргументами
      // result_arr, &exp_1 и &count_bit
      count_bit = 0;  // Устанавливаем значение count_bit в 0
      for (int i = 254; i >= 0; i--) {
        if (result_arr[i] == 1) *index_1 = 1;
        // Если элемент result_arr[i] равен 1, устанавливаем
        // значение *index_1 в 1
        if (*index_1) {
          count_bit++;
          // Если *index_1 равно 1, увеличиваем значение count_bit на 1
        }
      }
      (*index_2)--;  // Уменьшаем значение *index_2 на 1
      exp_1 = *index_2;  // Присваиваем значение *index_2 переменной exp_1
    }
  }
  return count_bit;  // Возвращаем значение count_bit
}

int set_exponent(int exp_1, s21_decimal *result) {
  int count_10_bit[8] = {0};  // Массив для хранения битов представления числа
                              // exp_1 в двоичной системе
  count10_to_bin(&exp_1, count_10_bit);
  // Преобразуем число exp_1 в двоичную систему и
  // сохраняем результат в массиве count_10_bit
  for (int i = 0, j = 16; i < 8; i++, j++) {
    if (count_10_bit[i]) {
      set_1_bit(&(result->bits[3]), j);
      // Устанавливаем j-й бит в 1 в поле bits[3] структуры
      // result, если i-й бит в count_10_bit равен 1
    } else {
      set_0_bit(&(result->bits[3]), j);
      // Устанавливаем j-й бит в 0 в поле bits[3] структуры
      // result, если i-й бит в count_10_bit равен 0
    }
  }
  return exp_1;  // Возвращаем значение exp_1
}

int set_sign(int sign_index, const int result_arr[], s21_decimal *result,
             int greater) {
  // Установка знака в соответствии с индексом sign_index
  if (sign_index == 2) set_1_bit(&(result->bits[3]), 31);
  // Если sign_index равен 2, устанавливаем 31-й бит в значении 1 в поле
  // bits[3] структуры result

  if (sign_index == 3 && greater == 0) {
    // Если sign_index равен 3 и greater равно 0
    int check_equal = 0;
    // Проверяем, есть ли в массиве result_arr хотя бы один бит со значением 1
    for (int i = 0; i < NUM_255; i++) {
      if (result_arr[i] == 1) {
        check_equal = 1;
        break;
      }
    }
    // Если найден хотя бы один бит со значением 1, устанавливаем 31-й бит в
    // значении 1 в поле bits[3] структуры result
    if (check_equal) set_1_bit(&(result->bits[3]), 31);
  } else if (sign_index == 4 && greater == 1) {
    // Если sign_index равен 4 и greater равно 1, устанавливаем 31-й бит в
    // значении 1 в поле bits[3] структуры result
    set_1_bit(&(result->bits[3]), 31);
  }
  return 0;
}

int perform_addition(const int *value_1_arr, const int *value_2_arr,
                     int *result_arr, int count_bit, int *index) {
  int memory = 0;  // Переменная для хранения значения переноса
                   // Цикл от текущего индекса *index до count_bit
  for (; *index < count_bit; (*index)++) {
    // Если оба бита равны 1
    if (value_1_arr[*index] == 1 && value_2_arr[*index] == 1) {
      if (memory == 0) {  // Если нет переноса
        result_arr[*index] = 0;  // Устанавливаем бит результата в 0
        memory = 1;  // Устанавливаем перенос в 1
      } else         // Если есть перенос
        result_arr[*index] = 1;  // Устанавливаем бит результата в 1
      // Если один из битов равен 1, а другой равен 0
    } else if ((value_1_arr[*index] == 0 && value_2_arr[*index] == 1) ||
               (value_1_arr[*index] == 1 && value_2_arr[*index] == 0)) {
      if (memory == 0) {  // Если нет переноса
        result_arr[*index] = 1;  // Устанавливаем бит результата в 1
      } else {                   // Если есть перенос
        result_arr[*index] = 0;  // Устанавливаем бит результата в 0
      }
      // Если оба бита равны 0
    } else if (value_1_arr[*index] == 0 && value_2_arr[*index] == 0) {
      if (memory == 0) {  // Если нет переноса
        result_arr[*index] = 0;  // Устанавливаем бит результата в 0
      } else {                   // Если есть перенос
        result_arr[*index] = 1;  // Устанавливаем бит результата в 1
        memory = 0;  // Сбрасываем перенос в 0
      }
    }
  }
  if (memory) {              // Если остался перенос
    result_arr[*index] = 1;  // Устанавливаем бит результата в 1
    count_bit++;  // Увеличиваем значение count_bit на 1
  } else {
    (*index)--;  // Уменьшаем значение *index на 1
  }
  return count_bit;  // Возвращаем значение count_bit
}

void perform_subtraction_greater(int *value_1_arr, const int *value_2_arr,
                                 int *result_arr, int count_bit, int *index) {
  // Производится вычитание для значений, где greater равно 1
  for (; *index < count_bit; (*index)++) {
    // Если текущие биты равны 0 и 0
    if (value_1_arr[*index] == 0 && value_2_arr[*index] == 0) {
      result_arr[*index] = 0;  // Результат равен 0
    }
    // Если текущий бит value_1_arr равен 1 и текущий бит value_2_arr равен 0
    else if (value_1_arr[*index] == 1 && value_2_arr[*index] == 0) {
      result_arr[*index] = 1;  // Результат равен 1
    }
    // Если текущий бит value_1_arr равен 0 и текущий бит value_2_arr равен 1
    else if (value_1_arr[*index] == 0 && value_2_arr[*index] == 1) {
      // Выполняется процедура переноса
      for (int j = (*index) + 1; j >= 0; j++) {
        if (value_1_arr[j] == 0) {
          value_1_arr[j] = 1;  // Инвертируем 0 на 1
        } else if (value_1_arr[j] == 1) {
          value_1_arr[j] = 0;  // Инвертируем 1 на 0
          break;
        }
      }
      result_arr[*index] = 1;  // Результат равен 1
    }
    // Если текущие биты равны 1 и 1
    else if (value_1_arr[*index] == 1 && value_2_arr[*index] == 1) {
      result_arr[*index] = 0;  // Результат равен 0
    }
  }
}

void perform_subtraction_lesser(const int *value_1_arr, int *value_2_arr,
                                int *result_arr, int count_bit, int *index) {
  // Производится вычитание для значений, где greater равно 0
  for (; *index < count_bit; (*index)++) {
    // Если текущие биты равны 0 и 0
    if (value_2_arr[*index] == 0 && value_1_arr[*index] == 0) {
      result_arr[*index] = 0;  // Результат равен 0
    }
    // Если текущий бит value_2_arr равен 1 и текущий бит value_1_arr равен 0
    else if (value_2_arr[*index] == 1 && value_1_arr[*index] == 0) {
      result_arr[*index] = 1;  // Результат равен 1
    }
    // Если текущий бит value_2_arr равен 0 и текущий бит value_1_arr равен 1
    else if (value_2_arr[*index] == 0 && value_1_arr[*index] == 1) {
      // Выполняется процедура переноса
      for (int j = (*index) + 1; j >= 0; j++) {
        if (value_2_arr[j] == 0) {
          value_2_arr[j] = 1;  // Инвертируем 0 на 1
        } else if (value_2_arr[j] == 1) {
          value_2_arr[j] = 0;  // Инвертируем 1 на 0
          break;
        }
      }
      result_arr[*index] = 1;  // Результат равен 1
    }
    // Если текущие биты равны 1 и 1
    else if (value_2_arr[*index] == 1 && value_1_arr[*index] == 1) {
      result_arr[*index] = 0;  // Результат равен 0
    }
  }
}

void perform_subtraction(int *value_1_arr, int *value_2_arr, int *result_arr,
                         int count_bit, int greater, int *index) {
  // Выполняется вычитание в зависимости от значения greater
  if (greater == 1) {
    // Если greater равно 1, вызываем функцию perform_subtraction_greater
    perform_subtraction_greater(value_1_arr, value_2_arr, result_arr, count_bit,
                                index);
  } else if (greater == 0) {
    // Если greater равно 0, вызываем функцию perform_subtraction_lesser
    perform_subtraction_lesser(value_1_arr, value_2_arr, result_arr, count_bit,
                               index);
  }
}

int align_exponents(s21_decimal *num1, s21_decimal *num2) {
  // Конвертируем число в десятичное и сохраняем экспоненту в переменную exp1
  int exp1 = s21_10_conv(*num1);
  // Конвертируем число в десятичное  и сохраняем экспоненту в переменную exp2
  int exp2 = s21_10_conv(*num2);
  if (exp1 > exp2) {  // Если экспонента exp1 больше экспоненты exp2
    *num2 = s21_superior_10(exp1, num2);
    // Изменяем число num2, увеличивая его экспоненту до exp1 с помощью функции
    // s21_superior_10
  } else if (exp2 > exp1) {  // Если экспонента exp2 больше экспоненты exp1
    *num1 = s21_superior_10(exp2, num1);
    // Изменяем число num1, увеличивая его экспоненту до exp2
    // с помощью функции s21_superior_10
  }
  return 0;  // Возвращаем 0
}

void initialize_value_1_arr(int value_1_arr[]) {
  for (int i = 0; i < NUM_255; i++) value_1_arr[i] = 2;
  // Инициализируем элементы массива value_1_arr значением 2
}

void convert_decimal_to_bits(s21_decimal src, int value_1_arr[]) {
  for (int i = 0; i < 96; i++) {
    if (test_bit(src.bits[i / 32], i % 32)) {
      value_1_arr[i] = 1;
      // Если бит i в поле bits структуры src установлен в 1, устанавливаем
      // элемент value_1_arr[i] в 1
    } else {
      value_1_arr[i] = 0;
      // Если бит i в поле bits структуры src установлен в 0, устанавливаем
      // элемент value_1_arr[i] в 0
    }
  }
}

int calculate_count_bit(const int value_1_arr[]) {
  int count_bit = 0;  // Счетчик битов
  int index_1 = 0;  // Флаг, указывающий на наличие единицы
  for (int i = 254; i >= 0; i--) {  // Цикл по индексам от 254 до 0
    if (value_1_arr[i] == 1) {  // Если текущий элемент равен 1
      index_1 = 1;  // Устанавливаем флаг index_1 в 1
    }
    if (index_1) {  // Если флаг index_1 установлен в 1
      count_bit++;  // Увеличиваем счетчик битов на 1
    }
  }
  return count_bit;  // Возвращаем количество установленных битов
}

int divide_by_10(int value_1_arr[], int *exp_1, int *count_bit) {
  int res = 0;
  int index_2 = *exp_1;
  while (index_2) {  // Пока index_2 не равен 0
    int index_1 = 0;
    // Деление числа, представленного массивом битов value_1_arr, на 10
    add_div_10(value_1_arr, exp_1, count_bit);
    *count_bit = 0;
    // Подсчитываем количество битов в числе после деления
    for (int i = 254; i >= 0; i--) {
      if (value_1_arr[i] == 1) {
        index_1 = 1;
      }
      // Если index_1 равен 1, увеличиваем счетчик битов count_bit
      if (index_1) {
        (*count_bit)++;
      }
    }
    index_2--;
  }
  // Если количество битов count_bit больше 32, возвращаем 1 (истина)
  // В противном случае возвращаем 0 (ложь)
  if (*count_bit > 32) {
    res = 1;
  }
  return res;
}

int check_bits(s21_decimal src) {
  int res = 0;
  // Проверяем биты в пределах индексов от 32 до 95 (не включая 96)
  for (int i = 32; i < 96; i++) {
    // Проверяем значение бита на позиции i в массиве src.bits
    // Сравниваем результат функции test_bit с 0
    // Если бит не равен 0, то возвращаем 1 (истина)
    if (test_bit(src.bits[i / 32], i % 32) != 0) {
      res = 1;
    }
  }
  // Если все проверяемые биты равны 0, возвращаем 0 (ложь)
  return res;
}

int convert_bits_to_int(int value_1_arr[], int count_bit) {
  int result = 0;
  // Преобразуем массив битов в целое число
  // Идем по каждому биту массива value_1_arr
  for (int i = 0; i < count_bit; i++) {
    // Если текущий бит равен 1, устанавливаем соответствующий бит в числе
    // result
    if (value_1_arr[i]) {
      set_1_bit_int(&result, i);
    } else {
      // Если текущий бит равен 0, сбрасываем соответствующий бит в числе result
      set_0_bit_int(&result, i);
    }
  }
  return result;  // Возвращаем полученное целое число
}

int equal_bits(s21_decimal num1, s21_decimal num2) {
  int res = 0;
  // Проверяем равенство соответствующих битов чисел num1 и num2
  // Если они равны, то продолжаем проверку следующих битов
  // Если они не равны, возвращаем 0 (ложь)
  if ((num1.bits[0] == num2.bits[0]) && (num1.bits[1] == num2.bits[1]) &&
      (num1.bits[2] == num2.bits[2]) && (num1.bits[3] == num2.bits[3])) {
    res = 1;
  }
  return res;
}

void count10_to_bin(int *count_10, int *count_10_bit) {
  int index = 0;  // Индекс текущего бита в массиве count_10_bit.
  while (*count_10) {  // Пока число не станет равным 0.
    int mod_2 = *count_10 % 2;  // Вычисляем остаток от деления на 2.
    count_10_bit[index] = mod_2;  // Записываем остаток в соответствующий бит
                                  // в массиве count_10_bit.
    *count_10 /= 2;  // Делим число на 2.
    index++;  // Увеличиваем индекс текущего бита в массиве count_10_bit.
  }
}

int add_less_1010(const int *arr_help, const int *arr_10) {
  int res = 0, flag = 0;
  for (int i = 0; i < 5 && !flag; i++) {
    if (arr_help[i] != arr_10[i]) {
      flag = 1;
      res = (arr_help[i] < arr_10[i]);
      // Возвращаем результат сравнения текущих битов.
      // Если текущий бит arr_help меньше текущего бита
      // arr_10, возвращаем 1, иначе 0.
    }
  }
  return res;
  // Если все биты равны, значит arr_help больше или равно числу 1010.
  // Возвращаем 0.
}

void add_element(int *arr_help, int *arr_10, const int *result_arr,
                 int *result_arr_copy, int *index, int *index_result,
                 int *start) {
  while (add_less_1010(arr_help, arr_10) && *index >= 0) {
    // Делаем сдвиг arr_help влево на 1 бит и записываем в последний элемент
    // еще одно число из result_arr.
    for (int i = 0; i < 4; i++) arr_help[i] = arr_help[i + 1];
    arr_help[4] = result_arr[*index];
    (*index)--;
    // Если добавили разряд, а число все еще меньше 1010, пишем 0 в
    // result_arr_copy. Здесь же учитываем индекс первого деления.
    if (!(*start) && add_less_1010(arr_help, arr_10)) {
      result_arr_copy[*index_result] = 0;
      (*index_result)++;
    }
  }
  // Обнуляем индекс первого деления.
  *start = 0;
}

void sub_1010(int *arr_help, const int *arr_10, int *arr_help_copy) {
  for (int i = 4; i >= 0; i--) {
    if (arr_help[i] == 0 && arr_10[i] == 0) {
      arr_help_copy[i] = 0;  // Если оба бита равны 0, устанавливаем
                             // соответствующий бит результата в 0
    } else if (arr_help[i] == 1 && arr_10[i] == 0) {
      arr_help_copy[i] = 1;  // Если старший бит равен 1, а младший бит равен 0,
                             // устанавливаем соответствующий бит результата в 1
    } else if (arr_help[i] == 0 && arr_10[i] == 1) {
      // Цикл для реализации ситуации, когда (10000 - 1010) и 1 нужно брать
      // не из соседнего разряда.
      for (int j = i - 1; j >= 0; j--) {
        if (arr_help[j] == 0) {
          arr_help[j] = 1;  // Если текущий бит равен 0, устанавливаем его в 1
        } else if (arr_help[j] == 1) {
          arr_help[j] = 0;  // Если текущий бит равен 1, устанавливаем его в 0 и
                            // прерываем цикл
          break;
        }
      }
      arr_help_copy[i] = 1;  // Устанавливаем соответствующий бит результата в 1
    } else if (arr_help[i] == 1 && arr_10[i] == 1) {
      arr_help_copy[i] = 0;  // Если оба бита равны 1, устанавливаем
                             // соответствующий бит результата в 0
    }
  }
}

// Длина функции 37 без коментов
void add_div_10(int *result_arr, int *exp_1, const int *count_bit) {
  // Массив result_arr_copy, в для записи результата деления на 10.
  int result_arr_copy[NUM_255];
  for (int i = 0; i < NUM_255; i++) result_arr_copy[i] = 2;
  // Массив arr_10, который будет использоваться для вычитания 1010 из числа.
  int arr_10[5] = {0, 1, 0, 1, 0};
  // Массив arr_help, который будет использоваться для хранения промежуточных
  // результатов вычитания.
  int arr_help[5], arr_help_copy[5];
  for (int i = 0; i < 5; i++) {
    arr_help[i] = 0;
    arr_help_copy[i] = 0;
  }
  // index - Индекс начала result_arr (первый элемент)
  // index_result - Индекс для записи результата  в result_arr_copy
  // start - Индекс первого деления, для сдвига и записи 0 в result_arr_copy
  int index = *count_bit - 1, index_result = 0, start = 1;
  // Заполняем arr_help первыми 4 цифрами result_arr индексами с 1 по 4, то
  // есть arr_help = 01010.
  for (int i = 1; i < 5; i++) {
    arr_help[i] = result_arr[index];
    index--;
  }
  // Цикл деления на 1010.
  while (index >= 0) {
    // Если число в arr_help меньше 1010, добавляем еще один элемент из
    add_element(arr_help, arr_10, result_arr, result_arr_copy, &index,
                &index_result, &start);
    // Если индекс ушел в отрицательное значение в прошлом цикле, завершаем,
    // поскольку дальше идет деление с остатком.
    if (index < 0 && add_less_1010(arr_help, arr_10)) break;
    // Процесс вычитания 1010 из arr_help.
    // Записываем в arr_help_copy полученный результат.
    sub_1010(arr_help, arr_10, arr_help_copy);
    // Когда вычитание произошло, записываем 1 в result_arr_copy.
    result_arr_copy[index_result] = 1;
    index_result++;
    // Обновляем arr_help.
    for (int i = 0; i < 5; i++) arr_help[i] = arr_help_copy[i];
  }
  // Записываем результат деления из result_arr_copy в result_arr.
  // Ищем конец результата в result_arr_copy.
  for (int i = 254; i >= 0; i--) {
    if (result_arr_copy[i] != 2) {
      index = i;
      break;
    }
  }
  // Используем start как индекс для записи в result_arr.
  start = 0;
  // Инициализация (по сути обнуление) result_arr, чтобы вписать туда новое
  // число.
  for (int i = 0; i < NUM_255; i++) result_arr[i] = 2;
  while (index >= 0) {
    // Записываем результат в result_arr.
    result_arr[start] = result_arr_copy[index];
    index--;
    start++;
  }
  // Уменьшаем экспоненту после деления на 1010.
  *exp_1 = *exp_1 - 1;
}

void set_1_bit(unsigned int *value, int BitNumber) {
  // Устанавливаем бит под номером BitNumber в значение 1 в переменной value
  // с помощью битовой операции ИЛИ с маской, у которой только бит под
  // номером BitNumber установлен в 1.
  *value |= 1u << BitNumber;
}

void set_1_bit_int(int *value, int BitNumber) {
  // Устанавливаем бит под номером BitNumber в значение 1 в переменной
  // value с помощью битовой операции ИЛИ с маской, у которой только бит под
  // номером BitNumber установлен в 1.
  *value |= 1u << BitNumber;
}

void set_0_bit(unsigned int *value, int BitNumber) {
  // Устанавливаем бит под номером BitNumber в значение 0 в переменной value
  // с помощью битовой операции И с маской, у которой только бит под
  // номером BitNumber установлен в 0.
  *value &= ~(1u << BitNumber);
}

void set_0_bit_int(int *value, int BitNumber) {
  // Устанавливаем бит под номером BitNumber в значение 0 в переменной
  // value с помощью битовой операции И с маской, у которой только бит под
  // номером BitNumber установлен в 0.
  *value &= ~(1u << BitNumber);
}

bool test_bit(unsigned int value, int BitNumber) {
  // Проверяем значение бита под номером BitNumber в переменной value с
  // помощью битовой операции И и возвращаем явное логическое значение.
  return (value & (1u << BitNumber)) != 0;
}

s21_decimal s21_superior_10(int power, s21_decimal *value) {
  int inferior =
      s21_10_conv(*value);  // Преобразуем число value в десятичное
                            // представление и сохраняем его в inferior
  s21_rev_10_conv(value, power);  // Преобразуем число value в семиразрядное
                                  // представление с основанием 10^power
  for (int i = 0; i < (power - inferior); i++) {
    mult_10(*value, value);
    // Умножаем число value на 10 (прибавляем ноль в конце)
  }
  return (*value);  // Возвращаем измененное значение value
}

int s21_shift(s21_decimal *number) {
  int vault_1 = 0;  // Хранит значение предыдущего бита
  int error = test_bit(number->bits[2], 31);
  // Проверка бита в старшем разряде третьего элемента
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 32; j++) {
      int vault_2 = test_bit((number->bits[i]), j);  // Сохраняет текущий бит
      if (vault_1) set_1_bit(&number->bits[i], j);
      // Устанавливаем бит в 1, если предыдущий бит равен 1
      else
        set_0_bit(&number->bits[i], j);
      // Устанавливаем бит в 0, если предыдущий бит равен 0
      vault_1 = vault_2;
      // Сохраняем текущий бит в vault_1 для следующей итерации
    }
  }
  // Возвращаем флаг ошибки (бит в старшем разряде третьего элемента)
  return error;
}

int s21_addiction_logic(s21_decimal value_1, s21_decimal value_2,
                        s21_decimal *result) {
  int prev = 0;  // Флаг, указывающий, была ли единица в уме
  int res;  // Бит, который будем записывать в результат
  int error = 0;  // Флаг ошибки (в данном коде не используется)
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 32; i++) {
      int next = 0;  // Флаг, указывающий, будем ли передавать единицу в
                     // следующий разряд
      // Проверка бита
      int a = test_bit(value_1.bits[j], i);  // Бит первого числа
      int b = test_bit(value_2.bits[j], i);  // Бит второго числа
      if (a == 0) {
        if (b == 0 && prev == 0) {
          res = 0;
          next = 0;
        } else if (b == 0 || prev == 0) {
          res = 1;
          next = 0;
        } else {
          res = 0;
          next = 1;
        }
      } else {
        if (b == 0 && prev == 0) {
          res = 1;
          next = 0;
        } else if (b == 0 || prev == 0) {
          res = 0;
          next = 1;
        } else {
          res = 1;
          next = 1;
        }
      }
      prev = next;
      // После получения значения res, устанавливаем соответствующий бит в
      // result
      if (res) {
        set_1_bit(&(result->bits[j]), i);
      } else {
        set_0_bit(&(result->bits[j]), i);
      }
    }
  }
  return error;  // Возвращаем флаг ошибки (в данном коде всегда равен 0)
}

void s21_rev_10_conv(s21_decimal *value, int result) {
  int power = 16;  // Переменная для хранения текущей степени числа 2
  // Проходим по битам мантиссы числа value в обратном порядке, начиная с 20-го
  // бита
  for (int i = 20; i > 15; i--, power /= 2) {
    // Если результат больше или равен текущей степени числа 2,
    // то устанавливаем соответствующий бит в 1 и вычитаем текущую степень из
    // результата
    if (result >= power) {
      result -= power;
      set_1_bit(&value->bits[3], i);
    } else {
      // Если результат меньше текущей степени, то устанавливаем соответствующий
      // бит в 0
      set_0_bit(&value->bits[3], i);
    }
  }
}

void mult_10(s21_decimal value, s21_decimal *result) {
  s21_decimal ins_val = value;
  // Сдвигаем значение ins_val на 1 разряд влево
  s21_shift(&ins_val);
  // Присваиваем результат сдвига ins_val переменной result
  *result = ins_val;
  // Сдвигаем значение ins_val на 2 разряда влево
  s21_shift(&ins_val);
  s21_shift(&ins_val);
  // Выполняем операцию сложения ins_val и *result и сохраняем результат в
  // *result
  s21_addiction_logic(*result, ins_val, result);
}

int s21_10_conv(s21_decimal value) {
  int result = 0;  // Переменная для хранения результата
  int power = 1;  // Переменная для хранения текущей степени числа 2
  // Проходим по битам мантиссы числа value, начиная с 16-го бита
  for (int i = 16; i < 21; i++, power = power * 2) {
    // Если i-й бит мантиссы равен 1, то добавляем соответствующую степень числа
    // 2 к результату
    if (test_bit(value.bits[3], i)) {
      result = result + power;
    }
  }
  return result;  // Возвращаем результат
}

int s21_is_less_num(s21_decimal num1, s21_decimal num2, int result) {
  // Сравниваем знаки чисел num1 и num2
  if (num1.bits[3] == num2.bits[3]) {
    // Сравниваем биты показателя степени чисел num1 и num2
    if (num1.bits[2] == num2.bits[2]) {
      // Сравниваем биты мантиссы чисел num1 и num2
      if (num1.bits[1] == num2.bits[1]) {
        // Сравниваем последний бит мантиссы чисел num1 и num2
        if (num1.bits[0] == num2.bits[0]) {
          result = 0;  // Числа равны, результат сравнения равен 0
        } else {
          result = compare_last_bit(num1.bits[0], num2.bits[0]);
          // Сравниваем последний бит мантиссы
        }
      } else {
        result = compare_last_bit(num1.bits[1], num2.bits[1]);
        // Сравниваем биты мантиссы
      }
    } else {
      result = compare_last_bit(num1.bits[2], num2.bits[2]);
      // Сравниваем биты показателя степени
    }
  } else {
    result = compare_exp_bits(num1, num2);
    // Сравниваем показатели степени чисел
  }
  return result;  // Возвращаем результат сравнения
}

int compare_last_bit(int bit1, int bit2) {
  int res = 0;
  // Сравниваем последний бит bit1 и bit2.
  if (bit1 < bit2) {
    // Если bit1 меньше bit2, возвращаем 1.
    res = 1;
  }
  // В остальных случаях возвращаем 0.
  return res;
}

int compare_exp_bits(s21_decimal num1, s21_decimal num2) {
  // Вычисляем десятичное значение для num1 и num2.
  int exp1 = s21_10_conv(num1);
  int exp2 = s21_10_conv(num2);
  // Сравниваем полученные десятичные значения.
  if (exp1 > exp2) {
    // Если десятичное значение num1 больше,
    // преобразуем num2 в более высокую экспоненту.
    num2 = s21_superior_10(exp1, &num2);
  } else if (exp2 > exp1) {
    // Если десятичное значение num2 больше,
    // преобразуем num1 в более высокую экспоненту.
    num1 = s21_superior_10(exp2, &num1);
  }
  // Сравниваем последний бит в разряде 2 для num1 и num2.
  return compare_last_bit(num1.bits[2], num2.bits[2]);
}

// Длина 44 без коментов
int s21_is_greater_num(s21_decimal num1, s21_decimal num2, int result) {
  // Сравнивем соотв. биты, если равны идем к след. разряду
  if (num1.bits[3] == num2.bits[3]) {
    if (num1.bits[2] == num2.bits[2]) {
      if (num1.bits[1] == num2.bits[1]) {
        if (num1.bits[0] == num2.bits[0]) {
          result = 0;
        } else if (num1.bits[0] > num2.bits[0]) {
          // Если бит num1 в разряде 0 больше бита num2,
          // результат устанавливаем в 1.
          result = 1;
        } else
          // В остальных случаях результат устанавливаем в 0.
          result = 0;
      } else if (num1.bits[1] > num2.bits[1]) {
        // Если бит num1 в разряде 1 больше бита num2,
        // результат устанавливаем в 1.
        result = 1;
      } else
        // В остальных случаях результат устанавливаем в 0.
        result = 0;
    } else if (num1.bits[2] > num2.bits[2]) {
      // Если бит num1 в разряде 2 больше бита num2,
      // результат устанавливаем в 1.
      result = 1;
    } else
      // В остальных случаях результат устанавливаем в 0.
      result = 0;
  } else {
    // Если биты num1 и num2 в разряде 3 не равны,
    // выполняем преобразование в десятичное число для обоих чисел.
    int exp1 = 0, exp2 = 0;
    exp1 = s21_10_conv(num1);
    exp2 = s21_10_conv(num2);
    // Сравниваем полученные десятичные значения.
    if (exp1 > exp2) {
      // Если десятичное значение num1 больше,
      // преобразуем num2 в более высокую экспоненту.
      num2 = s21_superior_10(exp1, &num2);
    } else if (exp2 > exp1)
      // Если десятичное значение num2 больше,
      // преобразуем num1 в более высокую экспоненту.
      num1 = s21_superior_10(exp2, &num1);
    // Продолжаем сравнение битов после преобразования в одинаковые экспоненты.
    if (num1.bits[2] == num2.bits[2]) {
      // Продолжаем сравнение битов в разряде 2.
      if (num1.bits[1] == num2.bits[1]) {
        // Продолжаем сравнение битов в разряде 1.
        if (num1.bits[0] == num2.bits[0]) {
          // Если биты num1 и num2 в разряде 0 равны,
          // результат устанавливаем в 0.
          result = 0;
        } else if (num1.bits[0] > num2.bits[0]) {
          // Если бит num1 в разряде 0 больше бита num2, результат устанавливаем
          // в 1
          result = 1;
        } else
          // В остальных случаях результат устанавливаем в 0.
          result = 0;
      } else if (num1.bits[1] > num2.bits[1]) {
        // Если бит num1 в разряде 1 больше бита num2,
        // результат устанавливаем в 1.
        result = 1;
      } else
        // В остальных случаях результат устанавливаем в 0.
        result = 0;
    } else if (num1.bits[2] > num2.bits[2]) {
      // Если бит num1 в разряде 2 больше бита num2,
      // результат устанавливаем в 1.
      result = 1;
    } else
      result = 0;
    // В остальных случаях результат устанавливаем в 0.
  }
  return result;
}

void cicle(const int *value_arr, int *value_min_exp) {
  for (int i = 0; i < NUM_255; i++) {
    // Копируем значения из массива value_arr в массив value_min_exp.
    value_min_exp[i] = value_arr[i];
  }
}

void slojenie(const int *value_min_exp, int *j, int *memory, int *index,
              int *result) {
  while (value_min_exp[*j] != 2) {
    // Проверяем значения битов value_min_exp[*j] и value_min_exp[*j - 2],
    // чтобы выполнить сложение разрядов.
    // Если оба бита равны 1, и нет дополнительного разряда в памяти,
    // результат в разряде *index будет 0, а значение memory будет установлено
    // в 1.
    if (value_min_exp[*j] == 1 && value_min_exp[*j - 2] == 1) {
      if (*memory == 0) {
        result[*index] = 0;
        *memory = 1;
      } else {
        result[*index] = 1;
      }
    }
    // Если один из битов равен 1, а другой равен 0,
    // и нет дополнительного разряда в памяти,
    // результат в разряде *index будет 1.
    else if ((value_min_exp[*j] == 0 && value_min_exp[*j - 2] == 1) ||
             (value_min_exp[*j] == 1 && value_min_exp[*j - 2] == 0)) {
      if (*memory == 0) {
        result[*index] = 1;
      } else {
        result[*index] = 0;
      }
    }
    // Если оба бита равны 0,
    // и нет дополнительного разряда в памяти,
    // результат в разряде *index будет 0.
    else if (value_min_exp[*j] == 0 && value_min_exp[*j - 2] == 0) {
      if (*memory == 0) {
        result[*index] = 0;
      } else {
        result[*index] = 1;
        *memory = 0;
      }
    }

    // Увеличиваем индекс и j для перехода к следующим разрядам.
    (*index)++;
    (*j)++;
  }
}

void slojenie_2_pervih_razryadov(const int *value_min_exp, int *j, int *memory,
                                 int *index, int *result) {
  for (int k = 0; k <= 1; k++, (*j)++, (*index)++) {
    // Проверяем значения бита value_min_exp[(*j) - 2] и memory,
    // чтобы выполнить сложение двух первых разрядов.
    // Если value_min_exp[(*j) - 2] равен 1 и memory равен 1,
    // результат в разряде *index будет 0.
    if (value_min_exp[(*j) - 2] == 1 && *memory == 1) {
      result[*index] = 0;
    }
    // Если value_min_exp[(*j) - 2] равен 0 и memory равен 1,
    // или value_min_exp[(*j) - 2] равен 1 и memory равен 0,
    // результат в разряде *index будет 1, а значение memory будет сброшено в 0.
    else if ((value_min_exp[(*j) - 2] == 0 && *memory == 1) ||
             (value_min_exp[(*j) - 2] == 1 && *memory == 0)) {
      result[*index] = 1;
      *memory = 0;
    }
    // Если value_min_exp[(*j) - 2] равен 0 и memory равен 0,
    // результат в разряде *index будет 0.
    else if (value_min_exp[(*j) - 2] == 0 && *memory == 0)
      result[*index] = 0;
  }
}
// 47 длина без коментов
int add_mul_1010(int *value_1_arr, int *value_2_arr, int *exp_1, int *exp_2) {
  int error = 0;  // флаг ошибки для переполнения
  // индекс для цикла умножения и массив где будет храниться промежуточный
  // результат
  int result[NUM_255], value_min_exp[NUM_255];
  int memory = 0, flag = 0;
  // нужен чтобы понимать какая экспонента меньше чтобы в конце цикла
  // увеличивать ее значение определяем разность показателей степеней и создаем
  // копию массива, который имеет малую экспоненту. Далее этот массив и будем
  // умножать на 10 пока экспоненты не станут равными
  int exp_delta = abs(*exp_1 - *exp_2);
  if (*exp_1 < *exp_2) {
    cicle(value_1_arr, value_min_exp);
    flag = 1;
  } else {
    cicle(value_2_arr, value_min_exp);
    flag = 2;
  }
  // умножаем на 10 (1010 в двоичной) пока дельта не станет = 0
  while (exp_delta) {  // инициализация каждый цикл
    int index = 0, j = 2;
    for (int i = 0; i < NUM_255; i++) result[i] = 2;
    // счет количества занятых битов для понимания "а можно ли вообще наше число
    // умножать на 10? А вдруг оно уже занимает 96 бита и после умножения не
    // поместится в decimal"
    int count_bit = 0, count_1_bits = 0;
    for (int i = 254; i >= 0; i--) {
      if (value_min_exp[i] == 1) {
        index = 1;
        count_1_bits++;
      }
      if (index) count_bit++;
    }
    index = 0;  // вернули индекс в прежнее значение
    // если единичных битов 96 или больше то умножать дальше -> будет
    // переполнение ставим error 123 (спец ошибка показывающая максимальное
    // заполнение decimal). Умножаем дальше, потому что может быть ситуация
    // когда
    //  MAX_DECIMAL - 0.07 и технически нужно записать в результат MAX_DECIMAL
    //  Oшибка сигнализирует о том, что у нас возможно произошло переполнение,
    // но так ли это, решается в основной функции, учитывая знаки cлагаемых
    if (count_1_bits >= 96) error = 123;
    // последний элемент всегда 0 при умножении на 10, а следующие два элемента
    // всегда копии
    result[index++] = 0;
    result[index] = value_min_exp[index - 1];
    index++;
    result[index] = value_min_exp[index - 1];
    index++;
    // цикл сложения
    slojenie(value_min_exp, &j, &memory, &index, result);
    // сложение первых двух разрядов
    slojenie_2_pervih_razryadov(value_min_exp, &j, &memory, &index, result);
    if (memory == 1) {
      result[index] = 1;
      memory = 0;
    }
    // поиск начала числа в result
    // запись в правильном порядке в новый массив
    // обновляем value_min_exp
    for (int k = 0; k < NUM_255; k++) value_min_exp[k] = result[k];
    // уменьшаем дельту и увеличиваем показатель экспоненты
    exp_delta--;
    if (flag == 1) {
      *exp_1 = *exp_1 + 1;
    } else if (flag == 2)
      *exp_2 = *exp_2 + 1;
  }
  if (flag == 1) {
    for (int k = 0; k < NUM_255; k++) value_1_arr[k] = value_min_exp[k];
  } else if (flag == 2)
    for (int k = 0; k < NUM_255; k++) value_2_arr[k] = value_min_exp[k];
  return error;
}

unsigned int exp_decimal_bin2dec(s21_decimal dst) {
  // Переменная для хранения десятичного значения показателя экспоненты.
  unsigned int exp_int = 0;
  // Степень двойки для вычисления десятичного значения показателя экспоненты.
  int exp_2 = 7;
  // Перебираем биты показателя экспоненты в обратном порядке до индекса 16.
  for (int index = 23; index >= 16; index--) {
    if (dst.bits[3] & (1u << index)) {
      // Если текущий бит равен 1, добавляем соответствующее значение степени
      // двойки к десятичному значению показателя экспоненты.
      exp_int += 1u << exp_2;
    }
    exp_2--;
  }
  return exp_int;  // Возвращаем десятичное значение показателя экспоненты со
                   // сдвигом относительно числа SIGN_POS.
}

int get_sign(s21_decimal *num) {
  int res = -1;
  // Проверяем значение бита в позиции 31 элемента num->bits[3],
  // чтобы определить знак числа.
  // Если бит равен 0, значит число положительное.
  if (test_bit(num->bits[3], 31) == 0) {
    res = 0;  // Устанавливаем результат в 0, если число положительное.
  } else {
    res = 1;  // Устанавливаем результат в 1, если число отрицательное.
  }
  return res;  // Возвращаем результат.
}

void set_bit(s21_decimal *num, int index) {
  // Устанавливаем бит с указанным индексом в числе num.
  // Вычисляем индекс элемента массива bits, который содержит биты числа.
  int array_index = index / 32;
  // Вычисляем смещение бита внутри элемента массива bits.
  int bit_offset = index % 32;
  // Устанавливаем бит с помощью побитовой операции "ИЛИ".
  // 1u << bit_offset создает маску, в которой только бит с индексом bit_offset
  // равен 1, а остальные биты равны 0. Затем выполняется побитовая операция
  // "ИЛИ" с текущим значением элемента массива bits, чтобы установить бит в
  // нужной позиции.
  num->bits[array_index] |= 1u << bit_offset;
}

void write_float_decimal_exp_more(const int *result, s21_decimal *dst,
                                  int index, int bit) {
  switch (bit) {
    case 0:
      // Записываем младшие 32 бита в младшую часть числа decimal.
      for (; index >= 0; index--) {
        if (result[index] == 1) set_1_bit(&(dst->bits[0]), index);
        // Если текущий бит равен 1, устанавливаем соответствующий бит в числе
        // decimal в 1.
      }
      break;
    case 1:
      // Записываем следующие 32 бита в среднюю часть числа decimal.
      for (; index >= 32; index--) {
        if (result[index] == 1) set_1_bit(&(dst->bits[1]), index - 32);
        // Если текущий бит равен 1, устанавливаем соответствующий бит в числе
        // decimal в 1.
      }
      // Записываем младшие 32 бита в младшую часть числа decimal.
      for (; index >= 0; index--) {
        if (result[index] == 1) set_1_bit(&(dst->bits[0]), index);
        // Если текущий бит равен 1, устанавливаем соответствующий бит в числе
        // decimal в 1.
      }
      break;
    case 2:
      // Записываем старшие 8 бит в старшую часть числа decimal.
      for (; index >= 64; index--) {
        if (result[index] == 1) set_1_bit(&(dst->bits[2]), index - 64);
        // Если текущий бит равен 1, устанавливаем соответствующий бит в числе
        // decimal в 1.
      }
      // Записываем следующие 32 бита в среднюю часть числа decimal.
      for (; index >= 32; index--) {
        if (result[index] == 1) set_1_bit(&(dst->bits[1]), index - 32);
        // Если текущий бит равен 1, устанавливаем  соответствующий бит в числе
        // decimal в 1.
      }
      // Записываем младшие 32 бита в младшую часть числа decimal.
      for (; index >= 0; index--) {
        if (result[index] == 1) set_1_bit(&(dst->bits[0]), index);
        // Если текущий бит равен 1, устанавливаем соответствующий бит в числе
        // decimal в 1.
      }
      break;
  }
}

void set_scale(s21_decimal *num, int exp) {
  // Создание битовой маски путем сдвига значения exp на 16 бит влево
  int bit_mask = exp << 16;
  // Присвоение битовой маски элементу массива bits с индексом 3 в структуре num
  num->bits[3] = bit_mask;
}
