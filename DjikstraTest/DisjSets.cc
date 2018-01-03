#include "DisjSets.h"
#include <iostream>
/**
 * Construct the disjoint sets object.
 * numElements is the initial number of disjoint sets.
 */
DisjSets::DisjSets( int numElements ) : s( numElements, -1 ){
    for (int x : s)
        s[x] = -1;
}

/**
 * Union two disjoint sets.
 * For simplicity, we assume root1 and root2 are distinct
 * and represent set names.
 * root1 is the root of set 1.
 * root2 is the root of set 2.
 */
bool DisjSets::unionSets( int root1, int root2 )
{
    //if they are NOT distinct, cancel.
    if (find(root1) == find(root2) || root1 == root2)
        return false;


    if( s[ root2 ] < s[ root1 ] )  // root2 is deeper
        s[ root1 ] = root2;        // Make root2 new root
    else
    {
        if( s[ root1 ] == s[ root2 ] )
            --s[ root1 ];          // Update height if same
        s[ root2 ] = root1;        // Make root1 new root
    }
    return true;
}


/**
 * Perform a find.
 * Error checks omitted again for simplicity.
 * Return the set containing x.
 */
int DisjSets::find( int x ) const
{
    if( s[ x ] < 0 )
        return x;
    else
        return find( s[ x ] );
}

int DisjSets::GetRoots(){
    int roots = 0;
    for(unsigned int i = 0; i < s.size(); ++i){
        if (s[i] < 1)
            ++roots;
    }
    return roots;
}



/**
 * Perform a find with path compression.
 * Error checks omitted again for simplicity.
 * Return the set containing x.
 */
int DisjSets::find( int x )
{
    if( s[ x ] < 0 )
        return x;
    else
        return s[ x ] = find( s[ x ] );
}

