.data
# 2 числа и ответы
a: .word 4
b: .word 5
c: .word 0
d: .word 0

.text
# загружаем 2 числа
lw $t1, a
lw $t2, b
# складываем и записываем
add $t3, $t2, $t1
sw $t3, c
# вычитаем и записываем
sub $t3, $t2, $t1
sw $t3, d

