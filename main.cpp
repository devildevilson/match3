﻿#include <iostream>
#include "simul_world.h"

using namespace devils_engine;

int main() {
  match3::simul_world w;
  w.init();
  w.run();
	return 0;
}

// значит что нам нужно: нужен движок 
// у меня пока что слабая связь системы ресурсов собственно с ресурсами
// в проекте мне нужно будет: описать ресурсы (звуки, шрифты, фигуры, скрипты, шейдеры)
// определить состояния игры и переход из одного в другое (загрузка, главное меню, игра)
// состояние игрового поля (возможно часть состояния игры, но вряд ли)
// (расстановка фигур на пустые слоты, проверка 3,4,5 в ряд, проверка на конец игры, ход игрока)
// подружить луа и систему ресурсов
// 