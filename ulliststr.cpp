#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE
void ULListStr::push_back(const std::string& val){
  /* check if the list is empty. if it is, then we create a new item and 
  assign the head and tail pointer to it. because the first list item
  and it's empty, we assign the tail first and last pointers to 0. */
  if(tail_ == nullptr){  
    tail_ = new ULListStr::Item(); 
    head_ = tail_;  
    tail_->first = 0; 
    tail_->last = 0; 
  }
  /* if the tail's last pointer is less than the array size, then this means 
  there is empty space at the back we can fill. we insert the val at the tail's last index.
  and then we increment the tail's last pointer to point at the new val. */
  if(tail_->last < ARRSIZE){ 
    tail_->val[tail_->last] = val; 
    tail_->last++; 
  }
  /* if the list is not empty and there isn't space to use in the tail item's array, 
  then we need to create a new item. the previous pointer of this new item will become 
  the old tail pointer. the old tail's next pointer becomes the new item. then, we update the
  tail to point at the new item. the tail item's first pointer will be 0 and the last
  pointer will be 1 because we are adding an item. then we insert the value at index 0 */
  else { 
    ULListStr::Item* newItem = new ULListStr::Item();
    newItem->prev = tail_; 
    tail_->next = newItem;
    tail_ = newItem;
    tail_->first = 0;
    tail_->last = 1;
    tail_->val[0] = val;
  }
  // finally, increment the size counter
  size_++; 
}

void ULListStr::pop_back(){
  // if the list is empty, we don't need to do anything!
  if(empty()){ 
    return;
  }
  // decrement the tail's last pointer because we are removing the current one
  tail_->last--; 
  // decrement the size counter too
  size_--; 
  /* if removing a value causes the item to be empty, then we need to get 
  rid of the item. we create a temp variable to hold this tail item. then, 
  the new tail becomes the old tail's previous pointer. we set the new tail's next
  pointer to null. if the tail is already null, this means the list is empty now 
  so the head needs to become null too. then we officially delete the removed item. */
  if(tail_->first == tail_->last){ 
    ULListStr::Item* temp = tail_;
    tail_ = tail_->prev;
    if(tail_ != nullptr){
      tail_->next = nullptr;
    }
    else{
      head_ = nullptr;
    }
    delete temp;
  }
}

void ULListStr::push_front(const std::string& val){
  /* check if the list is empty. if it is, then we create a new item and 
  assign the head and tail pointer to it. then we set the head first and last pointers
  to ARRSIZE because it signals an empty item while allowing push front logic to still work. */
  if(head_ == nullptr){
    head_ = new ULListStr::Item();
    tail_ = head_;
    head_->first = ARRSIZE;
    head_->last = ARRSIZE;
  }
  /* if there is room at the front of the array, then we can use that! 
  we decrement the head first pointer to point to the new front value. 
  then, we insert the value at this first index. */
  if(head_->first > 0){
    head_->first--;
    head_->val[head_->first] = val;
  }
  /* if the list isn't empty and there isn't room in the item's array, then we need to
  create a new item. this items next pointer becomes the head, and that head's previous pointer
  becomes the new item. then we update the head to point at the new item. this items first pointer
  will point to the ARRSIZE - 1 to account for the indexing. the last pointer becomes the ARRSIZE. for 
  the sake of working at the front, inserting values starting at the end of the array keeps open spaces. */
  else {
    ULListStr::Item* newItem = new ULListStr::Item();
    newItem->next = head_;
    head_->prev = newItem;
    head_ = newItem;
    head_->first = ARRSIZE - 1;
    head_->last = ARRSIZE;
    head_->val[head_->first] = val;
  }
  // increment the size counter
  size_++;
}

void ULListStr::pop_front(){
  // if the list is empty, we don't need to do anything!
  if(empty()){
    return;
  }
  /* increment the head item's first pointer because the 
  second index will become the first after removal */
  head_->first++;
  // decrement the size of the list
  size_--;
  /* if removal makes the item empty, then we need to remove the item from the list. to do this, 
  create a temporary item to keep track of this empty head item. then the new head will become the old 
  head's next pointed item. then assign null to this new head's previous pointer.
  if the head is null, then this means the entire list is empty so we make tail null too. 
  then delete the empty item.  */
  if(head_->first == head_->last){
    ULListStr::Item* temp = head_;
    head_ = head_->next;
    if(head_ != nullptr){
      head_->prev = nullptr;
    }
    else{
      tail_ = nullptr;
    }
    delete temp;
  }
}

// return a const reference to the back element 
std::string const& ULListStr::back() const{
  // throw an error if the list is emtpy
  if(empty()){
    throw std::out_of_range("list is empty");
  }
  // otherwise return the value at the tail items last index
  // subtract 1 from the index to account for 0
  return tail_->val[tail_->last - 1];
}

// return a const reference to the front element
std::string const& ULListStr::front() const{
  // if the list is empty, throw an error
  if(empty()){
    throw std::out_of_range("list is empty");
  }
  // otherwise return the value at the head items first index
  return head_->val[head_->first];
}

std::string* ULListStr::getValAtLoc(size_t loc) const {
  // if a non-existent location if provided, return null
  if(loc >= size_){
    return nullptr;
  }
  // create a temporary variable to track where we start
  ULListStr::Item* temp = head_;

  while(temp != nullptr){
    // get the size of this particular item's array
    size_t arraySize = temp->last - temp->first;
    // if this is the right item, return the pointer
    if(loc < arraySize){
      return &temp->val[temp->first + loc];
    }
    // otherwise, move to the next item
    loc -= arraySize;
    temp = temp->next;
  }
  
  return NULL;
}


void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
