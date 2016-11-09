// Andrew Bennett <andrew.bennett@unsw.edu.au>
// COMP1927 15s2 Prac question q2
// implement showKeys() to print all valid
// words in a Trie.

// The "main" function that actually does the work
// is "showKeysNode".

// helper function for debugging:
// prints out all information associated
// with a single Trie node
void printNode(Link node) {
    printf("keybit: %c\n", node->keybit);
    printf("finish: %d\n", node->finish);
    printf("data: \n");
    printf("->  %s\n", node->data.key);
    printf("->  %s\n", node->data.data);
    printf("child: %p\n", node->child);
    printf("sibling: %p\n", node->sibling);

}

// recursively call this on its siblings and children
// We make a new, separate function to do this from the
// "showKeys" we were asked to implement -- showKeys 
// takes in a Trie (which is a single pointer to a node),
// but we'll need to work with individual nodes/Links, hence
// our own separate function.
//
// It's probably easiest to approach this recursively. Anything
// we can do recursively we can do iteratively (using loop(s)),
// but sometimes one or the other is a lot easier.
//
// In this case, we can just think about how the different
// "cases" / states relate to each other. We can imagine we
// already have a function that does the work for us, and we
// just have to work out how to get from one node to another.
//
// It can be a bit hard to put into words, but hopefully it makes
// conceptual sense, at least on some level:
//
// If we simplify it down and imagine we're just looking at a
// linked list, it's a little easier to think about: we can do 
// something to the current node, and then move onto the next node
// by calling it on that node's "next" neighbour.
//
// So, if our list were like: H -> E -> L -> L -> O, if we called
// the function on the H node, to move onto the next we can just
// call the function on H's "next", thus moving onto the E.
//
// Let's say we have the words "HE" and "HELLO" as valid words in our
// trie. A valid word is marked by the end letter of that word being
// marked as an end letter -- so the 'E' and 'O' will both be
// marked as an end letter (node->finish == 1). 
//
// So, our algorithm could just go through each node, check whether
// it's a valid word, print it out if it is, then move onto the next
// letter in the word (by calling it on its next node).
//
// It would look something like this:
//
// note: I'm using the syntax 'f(H)' to refer to calling the function
// on the node that contains the letter H.
//
// f(H) would look at whether it's a valid finishing letter (it's not),
// then call it on the next letter along: F(E).
//
// f(E) checls whether it's a valid finishing letter -- it is! 
// so, we've found a word, so we can print it out. But there
// could still be more letters after this, so we call it on
// the next letter: f(L).
//
// f(L) isn't a valid end letter, so calls f(L) (the second L).
//
// f(L) isn't valid end letter, so calls f(O). O is a valid end letter,
// so we've found a word, "HELLO", so we can print that out.
//
// We've hit the end of the word now, but how does our function
// tell? Dereferencing NULL pointers is bad, so we want to 
// avoid accidentally trying to do things on a NULL pointer.
// We need to check somewhere whether we've hit the end --
// the simplest way is to just call the function on the next node
// anyway, even if it is NULL, then check at the start of the
// function that the node we've been given isn't NULL before
// doing anything else.
//
// A trie is slightly more complicated than a linked list, since
// it has "siblings" as well as children, as in our Trie might go:
//
// H -> (E) -> L -> L -> (O)
//   \
//      (I) -> Y -> (A)
//
//  (brackets to specify a valid end letter).
//
// It turns out it's actually really easy to
// extend our function to handle the slbings too -- just call
// the function on that pointer, as well as on the child pointer.
//
// Recursion is kind of confusing until you get your head
// around it, but with enough practice hopefully it will make sense :)


void showKeysNode(Link t) {
    // base case: the link is null
    if (t == NULL) {
        return;
    }

    // DEBUG: printNode
    // printNode(t);

    // case: this is a valid word, so print it out
    if (t->finish == 1) {
        printf("%s\n", t->data.key);
    }

    // call it on its children and siblings
    // we don't have to worry whether it's null here, because
    // we check that at the start of this function
    
    showKeysNode(t->sibling);
    showKeysNode(t->child);
}

// showKeys: display all Keys in Trie, one per line
// Just calls the function we've written on the root
// node of the Trie
void showKeys(Trie t)
{
    showKeysNode(t->root);
}
