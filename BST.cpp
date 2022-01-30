#if 0
// BST implementation for the Dictionary ADT
template <class Elem>
class BST {
private:
	BinNode<Elem>* root;   // Root of the BST
	int nodecount;         // Number of nodes
public:
	BST() { root = NULL; nodecount = 0; }
	~BST() { clearhelp(root); }
	clearhelp(BinNode<Elem>* subroot)
	{
		if (subroot == NULL) return;
		clearhelp(subroot->left());
		clearhelp(subroot->right());
		delete subroot;
	}
	bool find(const Elem& e) const
	{
		return findhelp(root, e);
	}
	bool findhelp(BinNode<Elem>* subroot, Elem& e)
	{
		if (subroot == NULL) return false;
		else if (e < subroot->val())
			return findhelp(subroot->left(), e);
		else if (e > subroot->val()))
		return findhelp(subroot->right(), e);
		else { return true; }
	}
	//return the root of the updated BST after insertion
	bool insert(const Elem& e) {
		root = inserthelp(root, e);
		nodecount++;
		return true;
	}
	BinNode<Elem>* inserthelp(BinNode<Elem>* subroot, const Elem& val) {
		if (subroot == NULL) // Empty: create node
			return new BinNodePtr<Elem>(val, NULL, NULL);
		if (val < subroot->val()))
		subroot->setLeft(inserthelp(subroot->left(), val));
		else
			subroot->setRight(inserthelp(subroot->right(), val));
		// Return subtree with node inserted
		return subroot;
	}
	//return the root of the updated tree after removal
	//t point to the removed node
	BinNode<Elem>* removehelp(BinNode<Elem>* subroot, const Elem& e, BinNode<Elem>*& t) {
		if (subroot == NULL) return NULL;
		else if (e < subroot->val())
			subroot->setLeft(removehelp(subroot->left(), e, t));
		else if (e > subroot->val())
			subroot->setRight(removehelp(subroot->right(), e, t));
		else { // Found it: remove it
			BinNode<Elem>* temp;
			t = subroot;
			if (subroot->left() == NULL)
				subroot = subroot->right();
			else if (subroot->right() == NULL)
				subroot = subroot->left();
			else {  // Both children are non-empty
				subroot->setRight(
					deletemin(subroot->right(), temp));
				Elem te = subroot->val();
				subroot->setVal(temp->val());
				temp->setVal(te);
				t = temp;
			}
		}
		return subroot;
	}
	//return the root of the tree after remove the node with the minimum value
	BinNode<Elem>* deletemin(BinNode<Elem>* subroot,
		BinNode<Elem>*& min) {
		if (subroot->left() == NULL) {
			min = subroot;
			return subroot->right();
		}
		else { // Continue left
			subroot->setLeft(
				deletemin(subroot->left(), min));
			return subroot;
		}
	}
#endif