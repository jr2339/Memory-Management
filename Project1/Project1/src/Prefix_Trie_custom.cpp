#include "../includes/Prefix_Trie_custom.hpp"

/*******************************************************************************

                                     Node()
    -Default constructor.  Initializes a node with no children.

 ******************************************************************************/

Node::Node(){
  A = (pointer) {};
  C = (pointer) {};
  G = (pointer) {};
  T = (pointer) {};
  terminal = 0;
}
/*******************************************************************************

                                     ~Node()
    -Default deconstructor.  Deletes each child node.

 ******************************************************************************/

//@@TODO
Node::~Node(){
  delete A;
  delete C;
  delete G;
  delete T;
}
/*******************************************************************************

                                     deepCopy()
    -Deep copies a node including its children.

 ******************************************************************************/

//@@TODO
Node *Node::deepCopy(){
  if (!this){
    return NULL;
  }
  Node *newNode = new Node();
  newNode->setTerminal(this->terminal);
  newNode->A = this->A->deepCopy();
  newNode->C = this->C->deepCopy();
  newNode->T = this->T->deepCopy();
  newNode->G = this->G->deepCopy();
  return newNode;
}
/*******************************************************************************

                                     getChild()
    -Returns the child specified by the parameter.  Currently only works for
       A C G T

 ******************************************************************************/

pointer Node::getChild(char child){
  switch(child){
  case 'A':
    return A;
  case 'C':
    return C;
  case 'G':
    return G;
  case 'T':
    return T;
  }
  return (pointer){};
}
/*******************************************************************************

                                     setChild()
    -Adds a child node specified by A C G T.  If the node already exists, just
       return it.

 ******************************************************************************/

//@@TODO
pointer Node::setChild(char child, int *size){
  switch(child){
  case 'A':
    if (getChild('A') == NULL){
       A = new Node();
       (*size)++;
    }
    return A;
  case 'C':
    if (!C){
       C = new Node();
       (*size)++;
    }
    return C;
  case 'G':
    if (!G){
       G = new Node();
       (*size)++;
    }
    return G;
  case 'T':
    if (!T){
       T = new Node();
       (*size)++;
    }
    return T;
  }
  return NULL;
}
/*******************************************************************************

                                     isTerminal()
    -Getter for "terminal"

 ******************************************************************************/

bool Node::isTerminal(){
  return terminal;
}

/*******************************************************************************

                                     setTerminal()
    -Setter for terminal. Indicates that a node is ther terminal point for some
       word.

 ******************************************************************************/

void Node::setTerminal(bool val){
  terminal = val;
}

/*******************************************************************************

                                     Trie()
    -Default constructor.  Initializes an empty trie (just a root).

 ******************************************************************************/

//@@TODO make pointer point to an actual node
Trie::Trie(MemoryAllocator *mem){
  memLocation = mem;
  size = 0;
  root = (pointer){};
}

/*******************************************************************************

                                     Trie()
    -Construct a trie from a set of sequences.  For now, all sequences must be 
       equal in length.

 ******************************************************************************/

//@@TODO
Trie::Trie(MemoryAllocator *mem, char **sequences, int nSeq, int seqLength){
  size = 0;
  root = (pointer){};
  pointer current = root;
  for(int i = 0; i<nSeq; i++){
    for(int j = 0; j < seqLength ; j++){
      current = current->setChild(sequences[i][j],&size);
    }
    current->setTerminal(1);
    current = root;
  }
}

/*******************************************************************************

                                     Trie()
    -Copy constructor.  Deep copies the trie that is passed as a parameter.

 ******************************************************************************/

//@@TODO
Trie::Trie(Trie *seed){
  size = seed->size;
  root = seed->root->deepCopy();
}

/*******************************************************************************

                                  ~Trie()
    -Generic deconstructor.  Relies on the underlying node deconstructor.

 ******************************************************************************/
//@@TODO
Trie::~Trie(){
  delete(root);
}

/*******************************************************************************

                                  addWord()
    -Add a word to the trie

 ******************************************************************************/

//@@TODO
void Trie::addWord(char *word, int wordLength){
  pointer current = root;
  for(int i = 0; i <wordLength; i++){
    current = current->setChild(word[i],&size);
  }
  current->setTerminal(1);
}

/*******************************************************************************

                                  searchWord()
    -Check if a word is in the Trie

 ******************************************************************************/

//@@TODO
bool Trie::searchWord(char *word, int wordLength){
  Node *current = root;
  for(int i = 0; i < wordLength; i++){
    // If the pointer is null, we can't go any farther, so the sequence
    //   is not in the tree.  Just return 0 / False.
    if (!(current = current->getChild(word[i]))){
      return 0;
    }
  }
  // If we made it all the way to the end of our target sequence, check if
  //   the node is terminal for some word.
  return current->isTerminal();
}



/*******************************************************************************

                                  Traverse()
    -Traverse an entire sequence and detect hits.
    -Returns the indices of the beginning of each hit.

 ******************************************************************************/
//@@TODO
std::vector<int> Trie::traverse(char *sequence, int seqLength, int wordSize){
  std::vector<int> indexVector;
  for(int i = 0; i<seqLength; i++){
    if(searchWord(&sequence[i], wordSize)){
      indexVector.insert(indexVector.end(),i);
    }
  }
  return indexVector;
}


/*******************************************************************************

                                  getSize()
    -Getter for Trie size.

 ******************************************************************************/

int Trie::getSize(){
  return this->size;
}

int main(int argc, char **argv){
  if(argc != 2){
    puts("Please supply exactly 2 input arguments.");
  }

  MemoryAllocator *memoryLayer = new MemoryAllocator(sizeof(pointer));
  Trie* prefixTrie = new Trie(memoryLayer);

  return 0;
}
