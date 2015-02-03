#include "Authority.hpp"

void Authority::cedeControlToPredecessor() const
{
	emit switchAuthority(predecessor_);
}

Authority *Authority::predecessor() const
{
	return predecessor_;
}

void Authority::onBecameReceiver(Authority *predecessor)
{}

void Authority::onNewMessage(Message &msg, UID sender)
{}

void Authority::becameReceiver(Authority *predecessor)
{
	predecessor_ = predecessor;
	onBecameReceiver(predecessor);
}
