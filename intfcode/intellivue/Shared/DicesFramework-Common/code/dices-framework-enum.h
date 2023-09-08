
#ifndef DICES_FRAMEWORK_ENUM_H_
#define DICES_FRAMEWORK_ENUM_H_

enum rs232_stopbits
{
  one_stopbit = 0,
  one_point_five_stopbits = 1,
  two_stopbits = 2
};

enum rs232_parity
{
  parity_none = 0,
  parity_even,
  parity_odd,
  parity_space
};

#endif // DICES_FRAMEWORK_ENUM_H_
