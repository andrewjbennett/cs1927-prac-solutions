// Andrew Bennett <andrew.bennett@unsw.edu.au>
// Week 13 Practice Prac q1 sample solution
//
// apply a function to the value in each node
//
// So, it sounds like we need to visit every node in the tree. 
// We can do "visit every node" using either a loop or recursion.
// In this case, I think recursion would be simpler, but there's 
// no reason we couldn't do it in a loop (using a stack or queue structure)
// In fact, recursion is sort of like getting an implicit stack data
// structure for free :)
//
// So, this will go something like:
//
// for the left and right children of our current sub-tree (aka current tree node):
//   call the map function (aka the function itself recursively) on those children
//
// We also need to apply the function we're meant to be applying -- but that's easy,
// we just need to call the function. It'll make sense in a minute.
//
// We also need to make sure we don't go off the end of the tree -- so stopping when
// we reach a leaf node. Rather than checking if the current node is a leaf node,
// it's a lot easier to assume both children are valid, then within this function
// stop if the current node is null.
// 
void map(BSTree t, int (*f)(int))
{
    // the previous node was a leaf node, and called this
    // function on a NULL pointer
    if (t == NULL) {
        return;
    }

    // We're not null, so it's safe to apply the function now
    t->value = f(t->value);

    // That line maybe looked kind of scary. Function pointers
    // are sort of magic. We effectively have a pointer called
    // f, but rather than pointing to an int or a node or whatever,
    // it's actually pointing to a function.
    //
    // We can call the function just like any other normal function
    //
    // We know the function takes in an int and returns an int 
    // (the two ints in the description of the function pointer), 
    // so we'll need to pass it the tree's value, and use the return
    // value of that function to update the tree's value.

    // get the left and right children to do this, too
    map(t->left, f);
    map(t->right, f);
}

