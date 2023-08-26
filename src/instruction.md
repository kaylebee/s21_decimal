# s21_decimal

## Содержание

1. [О проекте](#о-проекте)
2. [Навыки, полученные в ходе разработки](#навыки-полученные-закрепленные-в-ходе-разработки)
3. [Инструкция по сборке и запуску тестов](#инструкция-по-сборке-и-запуску-тестов)
4. [Команда разработчиков](#команда-разработчиков)

## О проекте

В данном проекте была разраотана библиотека на языке си, добавляющая возможность работы с типом "decimal", который отсутствует
в стандарте языка. Данный тип является аналогом decimal в языке C# (дробное число с фиксированной точкой). 

## Навыки, полученные (закрепленные) в ходе разработки
- Создание собственных типов данных
- Работа с побитовыми операциями
- Создание и связывание статических библиотек, сборка проекта с помощью Makefile
- Тестирование с помощью библиотеки Check
- Межязыковое тестирование с помощью языков C++ и C#

<br>

## Инструкция по сборке и запуску тестов
## Список всех команд

| Действие                       | Команда                                         |
| ------------------------------ | ----------------------------------------------- |
| Сборка и запуск всех тестов    | `make`                                          |
| Сборка библиотеки              | `make s21_decimal.a`                            |
| Запуск базовых тестов          | `make test;./test`                              |
| Запуск дополнительных тестов   | `make extended_test`                            |
| Формирование отчета о покрытии | `make gcov_report`                              |
| Стилевой тест                  | `make style`                                    |
| Тест на утечки                 | `make leaks`                                    |
| Запуск отчистки                | `make clean`                                    |

<br>

## Зависимости

**Шаг 1:**
Обновление информации о пакетах

```bash
sudo apt-get update
```

**Шаг 2:**
Установка LCOV (расширение GCOV)

```bash
sudo apt-get install lcov
```

**Шаг 3:**
Установка Mono (C# JIT compiler)

```bash
sudo apt-get install mono-complete
```

<br>
<br>

### Сборка и запуск всех тестов

```bash
make
```

---

### Сборка библиотеки

```bash
make s21_decimal.a
```

---

### Запуск базовых тестов

```bash
make test;./test
```

---

### Запуск дополнительных тестов

```bash
make extended_test
```

---

### Формирование отчета о покрытии

```bash
make gcov_report
```

---

### Стилевые тесты

```bash
make style
```

---

### Тест на утечки

```bash
make leaks
```

---

### Запуск отчистки

```bash
make clean
```

<br>

## Команда разработчиков

<table>
    <tbody>
        <tr>
            <td align="center" valign="middle">
                <a href="https://github.com/cheremshin" title="cheremshin">
                    <img valign="middle" width="64px" height="64px" src="https://avatars.githubusercontent.com/u/91583699?v=4">
                </a>
            </td>
            <td align="center" valign="middle">
                <a href="https://github.com/rozhnof" title="rozhnof">
                    <img valign="middle" width="64px" height="64px" src="https://avatars.githubusercontent.com/u/118114237?v=4">
                </a>
            </td>
            <td align="center" valign="middle">
                <a href="https://github.com/DanKee43" title="DanKee43">
                    <img valign="middle" width="64px" height="64px" src="https://avatars.githubusercontent.com/u/86988536?v=4">
                </a>
            </td>
        </tr>
        <tr>
            <td align="center" valign="middle">
                <a href="https://github.com/cheremshin" title="cheremshin">cheremshin</a>
            </td>
            <td align="center" valign="middle">
                <a href="https://github.com/rozhnof" title="rozhnof">rozhnof</a>
            </td>
            <td align="center" valign="middle">
                <a href="https://github.com/DanKee43" title="DanKee43">DanKee43</a>
            </td>
        </tr>
    </tbody>
</table>