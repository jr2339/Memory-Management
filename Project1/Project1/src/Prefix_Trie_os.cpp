#include "../includes/Prefix_Trie_os.hpp"

/*******************************************************************************

                                     Node()
    -Default constructor.  Initializes a node with no children.

 ******************************************************************************/

Node::Node(){
  A = NULL;
  C = NULL;
  G = NULL;
  T = NULL;
  terminal = 0;
}
/*******************************************************************************

                                     ~Node()
    -Default deconstructor.  Deletes each child node.

 ******************************************************************************/

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

Node *Node::getChild(char child){
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
  return NULL;
}
/*******************************************************************************

                                     setChild()
    -Adds a child node specified by A C G T.  If the node already exists, just
       return it.

 ******************************************************************************/

Node *Node::setChild(char child, int *size){
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

Trie::Trie(){
  size = 0;
  root = new Node();
}

/*******************************************************************************

                                     Trie()
    -Construct a trie from a set of sequences.  For now, all sequences must be 
       equal in length.

 ******************************************************************************/

Trie::Trie(char **sequences, int nSeq, int seqLength){
  size = 0;
  root = new Node();
  Node *current = root;
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

Trie::Trie(Trie *seed){
  size = seed->size;
  root = seed->root->deepCopy();
}

/*******************************************************************************

                                  ~Trie()
    -Generic deconstructor.  Relies on the underlying node deconstructor.

 ******************************************************************************/
Trie::~Trie(){
  delete(root);
}

/*******************************************************************************

                                  addWord()
    -Add a word to the trie

 ******************************************************************************/

void Trie::addWord(char *word, int wordLength){
  Node *current = root;
  for(int i = 0; i <wordLength; i++){
    current = current->setChild(word[i],&size);
  }
  current->setTerminal(1);
}

/*******************************************************************************

                                  searchWord()
    -Check if a word is in the Trie

 ******************************************************************************/

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
std::vector<int> Trie::traverse(char *sequence, int seqLength, int wordSize){
  std::vector<int> indexVector;
  for(int i = 0; i<seqLength; i++){
    if(searchWord(&sequence[i], wordSize)){
      indexVector.insert(indexVector.end(),i);
    }
  }
  return indexVector;
}

int parseLine(char* line){
     int i = strlen(line);
     const char* p = line;
     while (*p <'0' || *p > '9') p++;
           line[i-3] = '\0';
           i = atoi(p);
           return i;
}

int getValue() {
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmRSS:", 6) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}

/*******************************************************************************

                                  getSize()
    -Getter for Trie size.

 ******************************************************************************/

int Trie::getSize(){
  return this->size;
}


int main(int argc, char **argv) {
  
  Trie *prefixTrie = new Trie();

  ifstream infile("/common/contrib/classroom/inf503/project_1/test_reads.fasta");
  string str;
  char * seq;
  int lineNum;

  if(infile.is_open()) {

	seq = new char[50];
	lineNum = 1;
	int lazy = 0;
	while(getline(infile,str) && lazy < 100000) {
		if(lineNum%2==0) {
			for(int i = 0; i < 50; i++) 
				seq[i] = str[i];
			prefixTrie->addWord(seq, str.length());
		}
		lineNum++;
		lazy++;
	}
	
	int myMem;
	myMem = getValue();

	printf("Size of mem for OS: %d\n",myMem);

	delete[] seq;
	infile.close();

  } else
	printf("File does not exist\n");

  return 0;
}
