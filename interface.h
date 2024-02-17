#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

int getUserChoice(int option, int nodeCount);
int get_nodecount();
void addnode(int d);
void displaynodevalues();
void removenode(int nodeIndex);
int examinenode(int nodeIndex);
void changenodevalue(int nodeIndex, int newValue);
void sortnodes();

#endif // INTERFACE_H_INCLUDED
