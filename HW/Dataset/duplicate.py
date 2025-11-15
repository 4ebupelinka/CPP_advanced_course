import csv

input_file = "titanic.csv"
output_file = "big_titanic.csv"

# Сколько раз повторять данные
repeat_count = 100

with open(input_file, "r", newline="", encoding="utf-8") as infile, \
     open(output_file, "w", newline="", encoding="utf-8") as outfile:

    reader = csv.reader(infile)
    writer = csv.writer(outfile)

    # Читаем заголовок
    header = next(reader)
    writer.writerow(header)

    # Сохраняем все строки (кроме заголовка), чтобы не перечитывать файл 100 раз
    rows = list(reader)

    # Записываем строки 100 раз
    for _ in range(repeat_count):
        writer.writerows(rows)

print("Готово! Файл big_titanic.csv создан.")
