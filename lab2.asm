.data
# 2 ����� � �����
a: .word 50
b: .word 3
c: .word 0

.text
# �������� ����� � ��������
lw $t1, a
lw $t2, b
li $t3, 0
# �������
li $t0, 0

# ����
loop:
beq $t0, $t2, endloop # ���� ������� ����� ������� �����, ��������� ���������
add $t3, $t3, $t1 # �������� ������ ����� � ����������
addi $t0, $t0, 1 # ��������� ������� �� 1
j loop # ������� �� ��������� ��������

endloop:
sw $t3, c # ���������� ����������