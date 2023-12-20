# Работа по предмету Математический практикум

Начнём-с

## Пачка 3 
### Задача 1

Реализуйте функцию перевода числа из десятичной системы счисления в систему счисления с основанием 2<sup><i>r</i></sup>, <i>r</i> = 1,...,5. При реализации функции разрешается использовать битовые операции и операции обращения к памяти, запрещается использовать стандартные арифметические операции. Продемонстрируйте работу реализованной функции.

Основные функции:
&ensp; `plus(int num1, int num2)` с помощью битовых операций суммирует два числа.
&ensp; `negative(int n)` делает число отрицательным
&ensp; `reverse_string(char **string, int start, int length)` разворачивает строку
&ensp; `prepare(int base, int *mask, int *in_left)` производит валидации, и получает вспомогательную маску для числа
&ensp;  `number_to_cc(int number, int base, char **result)` выполняет перевод числа в нужную систему счисления.

Данное решение [31] на Cи реализует преобразование целых чисел из десятичной системы, в другую, через бинарные операции ^, & и ~. В коде реализованы также обработка ошибок и выделение памяти.

### Задача 2
Условие: 

Напишите функцию с переменным числом аргументов, на вход которой передаются: размерность пространства ; экземпляры структур, содержащие в себе координаты 𝑛 векторов из -мерного пространства; указатели на функции, вычисляющие нормы 𝑛 векторов. Ваша функция должна для каждой переданной нормы вернуть самый длинный переданный вектор (если таковых векторов несколько, необходимо вернуть их все)

Основные функции:
&ensp; `Vector **task(int num_vectors, int num_norms, ...)` Основная фунция вычисляющая для каждого вектора, все переданные нормы, и возвращающая двумерыный массив Векторов (самые длинные для каждой из норм).
&ensp; `print_vector(Vector *v)` вывод вектора в стандартный поток вывода
&ensp; `get_rand_vector(int n)` Получает вектор заполненный случайными значениями длины n.

Использованные структуры:
&ensp; `Vector` имеет кординаты, и размерность
&ensp; `norm_pointer` Указатель на функцию вычисляющую норму вектора.

В коде реализованы также обработка ошибок и выделение памяти. Пример работы программы: 

![Пример работы программы 3.2](/images/3_2.png)


### Задача 3

На вход программе через аргументы командной строки подается путь ко входному файлу, флаг (флаг начинается с символа ‘-’ или ‘/’, второй символ - ‘a’ или ‘d’) и путь к выходному файлу. В файле в каждой строчке содержится информация о сотруднике (для этой информации определите тип структуры Employee): id (целое неотрицательное число), имя (непустая строка только из букв латинского алфавита), фамилия (непустая строка только из букв латинского алфавита), заработная плата (неотрицательное вещественное число). Программа должна считать записи из файла в динамический массив структур и в выходной файл вывести данные, отсортированные (с флагом ‘-a’/‘/a’ - по возрастанию, с флагом ‘-d’/‘/d’ - по убыванию) первично - по зарплате, далее (если зарплаты равны) - по фамилии, далее (если зарплаты и фамилии равны) - по именам, наконец, по id. Для сортировки коллекции экземпляров структур используйте стандартную функцию qsort, своя реализация каких-либо алгоритмов сортировки не допускается

Основные функции:
&ensp; `validate_params` функция осуществляющая валидацию входных данных.
&ensp; `comp_right` и `comp_left` функции компараторы, для последующего использования в `qsort`.
&ensp; `print_employers` вывод информации о работниках.
&ensp; `scan_eployee` чтение информации о работнике из файла.
Использованные структуры и перечисления:
&ensp; `Employee` структура для информации о сотруднике, с полями по заданию.
&ensp; `statements` перечисление для типов ошибок, для их обработки.

В коде реализованы также обработка ошибок и выделение памяти. Ошибки имеют различные коды, которые программа обрабатывает. Пример работы программы: 

![Пример работы программы 3.3](/images/3_3.png)

### Задача 4

1. Опишите тип структуры String, содержащую в себе поля для указателя на
динамический массив символов типа char и количества символов (длины строки) типа int.

Для описанного типа структуры реализуйте функции:

● создания экземпляра типа String на основе значения типа char *
● удаления внутреннего содержимого экземпляра типа String
● отношения порядка между двумя экземплярами типа String (первично по длине строки, вторично по лексографическому компаратору)
● отношения эквивалентности между двумя экземплярами типа String (лексографический компаратор)
● копирования содержимого экземпляра типа String в существующий экземпляр
типа String
● копирования содержимого экземпляра типа String в новый экземпляр типа String, размещённый в динамической памяти
● конкатенации к содержимому первого экземпляра типа String содержимого
второго экземпляра типа String.

Продемонстрируйте работу реализованного функционала.

2. Экземпляр структуры Mail содержит в себе экземпляр структуры Address получателя (город (непустая строка), улица (непустая строка), номер дома (натуральное число), корпус (строка), номер квартиры (натуральное число), индекс получателя (строка из шести символов цифр)), вес посылки (неотрицательное вещественное число), почтовый идентификатор (строка из 14 символов цифр), время создания (строка в формате “dd:MM:yyyy hh:mm:ss”), время вручения (строка в формате “dd:MM:yyyy hh:mm:ss”). Экземпляр структуры Post содержит указатель на экземпляр структуры Address текущего почтового отделения и динамический массив экземпляров структур типа Mail. Реализуйте интерактивный диалог с пользователем, предоставляющий функционал для добавления и удаления объектов структур типа Mail в объект структуры типа Post, информативный вывод данных об отправлении при поиске объекта типа Mail по идентификатору. Объекты структуры Mail должны быть отсортированы по индексу получателя (первично) и идентификатору посылки (вторично) в произвольный момент времени. Также в интерактивном диалоге реализуйте опции поиска всех доставленных отправлений, а также всех отправлений, срок доставки которых на текущий момент времени (системное время) истёк. Информацию о доставленных/недоставленных отправлениях выводите в порядке времени создания по возрастанию (от старых к новым). Для хранения строковых данных используйте структуру String из п. 1.

Основные функции:

&ensp; `delete_adress` : Освобождает память, выделенную под структуру Adress.
&ensp; `delete_mail` : Освобождает память, выделенную под структуру Mail.
&ensp; `generate_post_id` : Генерирует случайный идентификатор почты.
&ensp; `print_adress`, `print_mail`, `print_mails`: Выводят информацию об адресе и почтовых отправлениях.
&ensp; `get_сurrent_time` : Возвращает текущее время в нужном формате.
&ensp; `parse_timestamp` : Преобразует строку времени в структуру tm.
&ensp; `add_mail` : Добавляет новое письмо в почтовое отделение.
&ensp; `search_mail`, `search_mails`: Ищут письмо по идентификатору или отсортированные списки доставленных и просроченных.
&ensp; `get_b_line`, `get_int`, `get_double`: Считывают строку, целое и вещественное число соответственно.
&ensp; `skip_empty`: Пропускает пустые символы.
&ensp; `track_mail`: Позволяет отслеживать и изменять статус почтового отправления.

Использованные структуры и перечисления:
&ensp; `Adress` структура для информации об адрессе.
&ensp; `Mail` структура для информации о почте, включающая в себя поле адресса.
&ensp; `Post` структура для информации об почтовом отделении.

Основной цикл работы программы, предоставляющий пользователю опции по работе с почтой реализован в  фунции `run`. Программа обеспечивает базовые операции добавления, отслеживания, сортировки и вывода почтовых отправлений. В коде реализованы также обработка ошибок и выделение памяти. Ошибки имеют различные коды, которые программа обрабатывает. 
Пример работы программы: 

![Пример работы программы 3.4](/images/3_4.png)

### Задача 5