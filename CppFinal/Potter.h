
#include <iostream>
#include "Moving.h"

class Potter : public Moving
{
private:
  int gems;

public:
  Potter();
  int getGems();
  void setGems(int);
};
