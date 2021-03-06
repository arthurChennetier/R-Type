//
// Created by simon on 26/01/18.
//

#ifndef GAME_MONSTERIA_H
#define GAME_MONSTERIA_H

#include <vector>

class MonsterIa
{
 public:
  MonsterIa()
  {
    _lenx = 400;
    _leny = 800;
  }

  virtual std::pair<float, float>
  getBestMove(std::vector<std::pair<float, float>> playerPos, std::pair<float, float> mypos)
  {
    return (std::make_pair<float, float>(0, 0));
  };

  virtual ~MonsterIa()
  = default;

 protected:
  float _lenx;
  float _leny;
};

#endif //GAME_MONSTERIA_H
