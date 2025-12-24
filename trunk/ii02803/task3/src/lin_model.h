/**
 * @file lin_model.h
 * @brief ������������ ���� � ����������� �������� ������ ������� ����������.
 *
 * �������� ������ ��������� ��������� ������� �� �������:
 * \f[
 *     y(k) = a \cdot y(k-1) + b \cdot u(k)
 * \f]
 */
#ifndef LIN_MODEL_H
#define LIN_MODEL_H
 /**
  * @brief �������� ������ ������������� �������.
  *
  * @param y_prev ���������� �������� ������ �������.
  * @param u ����������� �����������.
  * @param a ����������� �������� �����.
  * @param b ����������� �������� �� ������������ �������.
  * @return ����� �������� ������ �������.
  */
double l_model(double y_prev, double u, double a, double b);

#endif
