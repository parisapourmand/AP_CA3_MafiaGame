#include "player.hpp"

Player::Player()
{
	life = 1;
}

void Player::setVote(std::string voteeName)
{
	vote = voteeName;
}

void Player::decreaseLife()
{
	life--;
}