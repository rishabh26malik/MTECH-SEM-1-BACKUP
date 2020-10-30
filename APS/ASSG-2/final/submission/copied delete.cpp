node* deleteNode(node* root, T key)  
{  
      
    if (root == NULL)  
        return root;  
    if ( key < root->val )  
        root->left = deleteNode(root->left, key);  
    else if( key > root->val )  
        root->right = deleteNode(root->right, key); 
    else
    {  
        if( (root->left == NULL) || 
            (root->right == NULL) )  
        {  
            node *temp = root->left ?  
                         root->left :  
                         root->right;  
  
            // No child case  
            if (temp == NULL)  
            {  
                temp = root;  
                root = NULL;  
            }  
            else // One child case  
            *root = *temp; // Copy the contents of  
                           // the non-empty child  
            delete(temp);  
        }  
        else
        {  
        	node *tmp=root->right;
	            while(tmp->left){
	                tmp=tmp->left;
	            }
	            root->val=tmp->val;
	            root->right=deleteNode(root->right, tmp->val);
              
        }  
    }  
  
    // If the tree had only one node 
    // then return  
    if (root == NULL)  
    	return root;  
  	int lHeight = (root->left) ? root->left->height : 0;
	int rHeight = (root->right) ? root->right->height : 0;
	root->height= max(lHeight , rHeight) + 1;
	int height_diff=getHeightDiff(root);
	if(height_diff > 1){			//	LEFT HEIGHT MORE
		if(getHeightDiff(root->left)>=0){			// LL
			cout<<"in LL condn...\n";
			return LL_rotate(root);
		}
		else if (getHeightDiff(root->left)<0){	// LR
			cout<<"in LR condn...\n";
			return LR_rotate(root);
		}
	}
	else if(height_diff < -1){   	//	RIGHT HEIGHT MORE
		if(getHeightDiff(root->right)>0){			// RL
			cout<<"in RL condn...\n";
			return RL_rotate(root);
		}
		else if (getHeightDiff(root->right)<=0){	// RR
			cout<<"in RR condn...\n";
			return RR_rotate(root);
		}
	} 
	updateSubtreeSize(root);
	return root;

}  

	node* deleteNode_util(node* root, T key) {
	    cout<<"in del...\n";
	    if(!root){
	    	SIZE--;
	        return root;
	    }
	    node *tmp;
	    if(key < root->val){
	        root->left=deleteNode_util(root->left, key);
	    }
	    else if (key > root->val){
	        root->right=deleteNode_util(root->right, key);
	    }
	    else{
	        /*if(!root->left && !root->right){
	        	cout<<"in leaf...\n";
	            tmp=root;
	            root=NULL;
	            delete(tmp);
	            //return NULL;
	        }
	        else if(!root->left || !root->right){
	        	cout<<"in 1 child...\n";
	            tmp=(root->left) ? root->left : root->right;
	            root=tmp;
	            delete(tmp);
	            //return tmp;
	        }*/
	        if(!root->left || !root->right){
	        	node *tmp=(root->left) ? root->left : root->right;
	        	if(!tmp){
	        		tmp=root;
	        		root=NULL;
	        	}
	        	else
	        		*root=*tmp;
	        	delete(tmp);
	        }
	        else{
	        	cout<<"in 2 child...\n";
	            node *tmp=root->right;
	            while(tmp->left){
	                tmp=tmp->left;
	            }
	            root->val=tmp->val;
	            root->right=deleteNode_util(root->right, tmp->val);
	        }
	    }
	    /*if (root == NULL)  
	    	return root;
	    int lHeight = (root->left) ? root->left->height : 0;
		int rHeight = (root->right) ? root->right->height : 0;
		root->height= max(lHeight , rHeight) + 1;
	    int height_diff=getHeightDiff(root);
		if(height_diff > 1){			//	LEFT HEIGHT MORE
			if(root->left && key < root->left->val){			// LL
				cout<<"in LL condn...\n";
				return LL_rotate(root);
			}
			else if (root->left && key > root->left->val){	// LR
				cout<<"in LR condn...\n";
				return LR_rotate(root);
			}
		}
		else if(height_diff < -1){   	//	RIGHT HEIGHT MORE
			if(root->right && key < root->right->val){			// RL
				cout<<"in RL condn...\n";
				return RL_rotate(root);
			}
			else if (root->right && key > root->right->val){	// RR
				cout<<"in RR condn...\n";
				return RR_rotate(root);
			}
		} 
		updateSubtreeSize(root);
		return root;*/

		if (root == NULL)  
	    	return root;  
	  	int lHeight = (root->left) ? root->left->height : 0;
			int rHeight = (root->right) ? root->right->height : 0;
			root->height= max(lHeight , rHeight) + 1;
		    int height_diff=getHeightDiff(root);
			if(height_diff > 1){			//	LEFT HEIGHT MORE
				if(getHeightDiff(root->left)>=0){			// LL
					cout<<"in LL condn...\n";
					return LL_rotate(root);
				}
				else if (getHeightDiff(root->left)<0){	// LR
					cout<<"in LR condn...\n";
					return LR_rotate(root);
				}
			}
			else if(height_diff < -1){   	//	RIGHT HEIGHT MORE
				if(getHeightDiff(root->right)>0){			// RL
					cout<<"in RL condn...\n";
					return RL_rotate(root);
				}
				else if (getHeightDiff(root->right)<=0){	// RR
					cout<<"in RR condn...\n";
					return RR_rotate(root);
				}
			} 
			updateSubtreeSize(root);
			return root;

	}
