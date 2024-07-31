#include "../classes.hpp"
#include "../conv_db.hpp"

Conversation *conv1 = new DMConversation(u1, u2);
Conversation *conv2 = new DMConversation(u1, u5);
Conversation *conv3 = new DMConversation(u1, u7);
CommunityConversation *cconv = new FreeJoinCommunity(u2);
cconv->joinCommunity(u1);

store_conv(conv1);
store_conv(conv2);
store_conv(conv3);
store_conv(cconv);