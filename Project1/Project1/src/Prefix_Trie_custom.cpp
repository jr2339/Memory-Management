#include "../includes/Prefix_Trie_custom.hpp"

MemoryAllocator<Node> *memLayer;
/***************************************************************************//**
 *
 *                                    Node()
 *   -Default constructor.  Initializes a node with no children.
 *
 ******************************************************************************/

Node::Node(){
  A = (pointer) {.page = {255,255,255}, .offset = {255,255}};
  C = (pointer) {.page = {255,255,255}, .offset = {255,255}};
  G = (pointer) {.page = {255,255,255}, .offset = {255,255}};
  T = (pointer) {.page = {255,255,255}, .offset = {255,255}};
  terminal = 0;
}



/***************************************************************************//**
 *
 *                                    ~Node()
 *    -Default deconstructor.  Deletes each child node.
 *
 ******************************************************************************/
//@@TODO
Node::~Node(){
  //
}


/*******************************************************************************

                                     deepCopy()
    -Deep copies a node including its children.

******************************************************************************/

/*
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
*/

/***************************************************************************//**
 *
 *                                    getChild()
 *   -Returns the child specified by the parameter.  Currently only works for
 *      A C G T
 *   @param child The character indicator [A|C|G|T] of the child we want to get.
 *   @return The pointer of the child node or a null pointer if child doesn't
 *      exist.
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
  return (pointer){.page={255,255,255}, .offset={255,255}};
}

/***************************************************************************//**
 *
 *                                    setChild()
 *   -Adds a child node specified by A C G T.  If the node already exists, just
 *      return it.
 *   @param child The child we wish to set
 *   @param[out] size A pointer to the size of the current trie.
 *   @return A pointer to the new node or existing child.
 ******************************************************************************/

pointer Node::setChild(char child, int *size){
  uint64_t page = 0;
  switch(child){
  case 'A':
    if (isNull(getChild('A'))){
      A = memLayer->smalloc();
      page = charsToUint64(getChild('A').page,(char)NPAGECHARS);
      uint64_t offset = charsToUint64(A.offset, (char)NOFFSETCHARS);
      (memLayer->getPages().at(page))->set(offset, Node());
      (*size)++;
      puts("A is null");
    }
    return A;
  case 'C':
    if (isNull(getChild('C'))){
      C = memLayer->smalloc();
      page = charsToUint64(getChild('C').page,(char)NPAGECHARS);
      uint64_t offset = charsToUint64(C.offset, (char)NOFFSETCHARS);
      (memLayer->getPages().at(page))->set(offset, Node());
      (*size)++;
      puts("C is null");
    }
    return C;
  case 'G':
    if (isNull(getChild('G'))){
      G = memLayer->smalloc();
      page = charsToUint64(getChild('G').page,(char)NPAGECHARS);
      uint64_t offset = charsToUint64(G.offset, (char)NOFFSETCHARS);
      (memLayer->getPages().at(page))->set(offset, Node());
      (*size)++;
      puts("G is null");
    }
    return G;
  case 'T':
    if (isNull(getChild('T'))){
      T = memLayer->smalloc();
      page = charsToUint64(getChild('T').page,(char)NPAGECHARS);
      uint64_t offset = charsToUint64(T.offset, (char)NOFFSETCHARS);
      (memLayer->getPages().at(page))->set(offset, Node());
      (*size)++;
      puts("T is null");
    }
    return T;
  }
  return (pointer){.page = {255,255,255},.offset={255,255}};
}
/***************************************************************************//**
 *
 *                                    isTerminal()
 *   -Getter for "terminal"
 *   @return True if the node is terminal, false otherwise.
 ******************************************************************************/

bool Node::isTerminal(){
  return terminal;
}

/***************************************************************************//**
 *
 *                                     setTerminal()
 *   -Setter for terminal. Indicates that a node is ther terminal point for some
 *      word.
 *   @param val The new value for terminal.
 ******************************************************************************/

void Node::setTerminal(bool val){
  terminal = val;
}

/***************************************************************************//**
 *
 *                                    Trie()
 *   -Default constructor.  Initializes an empty trie (just a root).
 *
 ******************************************************************************/

Trie::Trie(){
  size = 0;
  root = memLayer->smalloc();
  uint64_t page = charsToUint64(root.page, NPAGECHARS);
  uint64_t offset = charsToUint64(root.offset, NOFFSETCHARS);
  (memLayer->getPages().at(page))->set(offset, Node());
}



/***************************************************************************//**
 *
 *                                    Trie()
 *   -Construct a trie from a set of sequences.  For now, all sequences must be
 *      equal in length.
 *   @param sequences The array of sequences from which we will construct our
 *      trie.
 *   @param nSeq The number of sequences.
 *   @param seqLength The length of each sequence.
 ******************************************************************************/

Trie::Trie(char **sequences, int nSeq, int seqLength){
  size = 0;
  root = memLayer->smalloc();
  pointer current = root;
  Node *cNode;
  for(int i = 0; i<nSeq; i++){
    for(int j = 0; j < seqLength ; j++){
      cNode = (memLayer->getPages()).at(charsToUint64(current.page, NPAGECHARS))->
        get_memory_of(charsToUint64(current.offset, NOFFSETCHARS));
      current = cNode->setChild(sequences[i][j],&size);
    }
    cNode->setTerminal(1);
    current = root;
  }
}

/*******************************************************************************

                                     Trie()
    -Copy constructor.  Deep copies the trie that is passed as a parameter.

******************************************************************************/

//@@TODO
/*
  Trie::Trie(Trie *seed){
  size = seed->size;
  root = seed->root->deepCopy();
  }
*/

/*******************************************************************************

                                  ~Trie()
    -Generic deconstructor.  Relies on the underlying node deconstructor.

******************************************************************************/
//@@TODO
/*
  Trie::~Trie(){
  delete(root);
  }
*/

/***************************************************************************//**
 *
 *                                 addWord()
 *   -Add a word to the trie
 *   @param word The word that we want to add to our trie.
 *   @param wordLength The length of the word that we want to add.
 ******************************************************************************/

void Trie::addWord(char *word, int wordLength){
  pointer current = root;

  Node *cNode;

  for(int i = 0; i <wordLength; i++){
    cNode = (memLayer->getPages()).at(charsToUint64(current.page, NPAGECHARS))->
      get_memory_of(charsToUint64(current.offset, NOFFSETCHARS));
    current = cNode->setChild(word[i],&size);
  }
  cNode->setTerminal(1);
}

/***************************************************************************//**
 *
 *                                 searchWord()
 *   -Check if a word is in the Trie
 *   @param word The word for which we want to search.
 *   @param wordLength The length of the word for which we wish to search.
 *   @return True if the word was found, false if it was not.
 ******************************************************************************/

bool Trie::searchWord(char *word, int wordLength){
  pointer current = root;
  Node *cNode;
  for(int i = 0; i < wordLength; i++){
    // If the pointer is null, we can't go any farther, so the sequence
    //   is not in the tree.  Just return 0 / False.
    if(isNull(current)){
      return 0;
    }
    cNode = (memLayer->getPages()).at(charsToUint64(current.page, NPAGECHARS))->
      get_memory_of(charsToUint64(current.offset, NOFFSETCHARS));
    current = cNode->getChild(word[i]);
  }
  // If we made it all the way to the end of our target sequence, check if
  //   the node is terminal for some word.
  return cNode->isTerminal();
}



/*******************************************************************************

                                  Traverse()
    -Traverse an entire sequence and detect hits.
    -Returns the indices of the beginning of each hit.

******************************************************************************/
//@@TODO
/*
  std::vector<int> Trie::traverse(char *sequence, int seqLength, int wordSize){
  std::vector<int> indexVector;
  for(int i = 0; i<seqLength; i++){
  if(searchWord(&sequence[i], wordSize)){
  indexVector.insert(indexVector.end(),i);
  }
  }
  return indexVector;
  }
*/


/***************************************************************************//**
 *
 *                                 getSize()
 *   -Getter for Trie size.
 *   @return The size of the trie (in number of nodes).
 ******************************************************************************/

int Trie::getSize(){
  return this->size;
}

int main(int argc, char **argv){
  memLayer = new MemoryAllocator<Node>();
  Trie *prefixTrie = new Trie();
  // prefixTrie->setMemLayer((void*)memoryLayer);
  //Add first, check size
  prefixTrie->addWord((char*)"ACTGACTGACTG",12);
  printf("Size: %d\n", prefixTrie->getSize());
  //Add second, all new - should be 12 more
  prefixTrie->addWord((char*)"CTGACTGACTAT",12);
  printf("Size: %d\n", prefixTrie->getSize());
  //Add same sequence, should still be 24
  prefixTrie->addWord((char*)"CTGACTGACTAT",12);
  printf("Size: %d\n", prefixTrie->getSize());
  //Add some of the same, then branch, should be 30
  prefixTrie->addWord((char*)"CTGACTTGACTG",12);

  //Search sequence hit
  printf("%d\n",prefixTrie->searchWord("ACTGACTGACTG",12));
  //Search sequence miss due to non terminal node
  printf("%d\n",prefixTrie->searchWord("ACT",3));
  //Search sequence miss due to beginning in the middle
  printf("%d\n",prefixTrie->searchWord("GACTG",5));
  //Search sequence hit
  printf("%d\n",prefixTrie->searchWord("CTGACTGACTAT",12));
  //Add different size node and try again
  prefixTrie->addWord((char*)"ACT",3);
  //Search sequence hit
  printf("%d\n",prefixTrie->searchWord("ACT",3));

  //Check final size - shouldn't have changed.
  printf("Size: %d\n", prefixTrie->getSize());

  exit(EXIT_SUCCESS);
}
