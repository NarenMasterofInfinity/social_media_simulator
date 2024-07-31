#include "classes.hpp"
#include "user_methods.hpp"
#include "conv_db.hpp"
#include "text_methods.hpp"

#ifndef CONV_METHODS_H
#define CONV_METHODS_H

Conversation *search_dm_conversations(User user1, User user2)
{
    return search_dm_conversations(user1.getUsername(), user2.getUsername());
}
Conversation *search_dm_conversations(User *user1, User *user2)
{
    return search_dm_conversations(*user1, *user2);
}

bool compare_fn(const Message* m1, const Message *m2){
	int t1 = m1->created_at;
	int t2 = m2->created_at;
	return t2 > t1;
}
void Conversation::restore_chat(){
	while (!history.empty()){
		Message* msg = history.top();
		chats_msgs.root = chats_msgs.insert_node(chats_msgs.root,msg);
		history.pop();
	}
	
}

void Conversation::restore_message(Message *msg){
	stack<Message*> temp;
	while(!history.empty()){
		Message *m = history.top();
		if(m == msg){
			history.pop();
			temp.push(msg);
			chats_msgs.root = chats_msgs.insert_node(chats_msgs.root,msg);
		}
		else{
			temp.push(m);
			history.pop();
		}
	}
	while(!temp.empty()){
		history.push(temp.top());
		temp.pop();
	}
}
void Conversation::delete_message(Message *msg){
	int s = chats_msgs.size(chats_msgs.root);
	chats_msgs.root = chats_msgs.delete_node(chats_msgs.root, msg);
	if(chats_msgs.size(chats_msgs.root) != s){
		history.push(msg);
	}
}

void Conversation::sendMessage(Message* msg){
	sleep(1);
	msg->created_at = time(NULL);
	chats_msgs.root = chats_msgs.insert_node(chats_msgs.root,msg);
	string usr =  (msg->getAuthor())->getUsername();
	this->sendNotifications(usr);
}

void Conversation::sendNotifications(string from){
	string msg;
	switch (this->getType())
	{
	case NORMAL_CONV:
		msg = "You got a message from the DM with ";
		break; 
	
	case COMMUNITY_CONV:
		msg = "You got a message from the Community " + this->getCommunityName() + " from ";
		break;
	
	case GROUP_CONV:
		msg = "You got a message from the Group "+this->group_name + "from ";
		break;
	default:
		msg = "";
		break;
	}
	msg += from;
	Notification n{msg};
	n.setPriority(this->priority*time(NULL));
	n.setConversation(this);
	//vector<User*>::iterator ui;
	for(int i = 0; i < participants.size(); i++){
		if(! participants[i]){
			return;
		}
		if(participants[i]->getUsername() != from){
			participants[i]->change = 50;
			participants[i]->notifications.insert(n);
		}
	}
}
#endif
