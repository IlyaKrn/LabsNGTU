.data
# 2 ����� � ������
a: .word 4
b: .word 5
c: .word 0
d: .word 0

.text
# ��������� 2 �����
lw $t1, a
lw $t2, b
# ���������� � ����������
add $t3, $t2, $t1
sw $t3, c
# �������� � ����������
sub $t3, $t2, $t1
sw $t3, d

