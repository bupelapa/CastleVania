#include "Obstaculo.hpp"

Obstaculo::Obstaculo(sf::Vector2f pos, sf::Vector2f hit, int efet, ID::ids id) :
	Entidade(id, pos, hit), efeito(efet){


}
