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

// WRITE YOUR CODE HERE
void ULListStr::push_back(const std::string& val){
   //case 1: create new item
  if(size_ == 0){
    tail_ = new Item();
    head_ = tail_;
    tail_->val[0] = val;
    tail_->last++, size_++;
  }
  //case 2: enough space in the back
  else if(tail_->last < ARRSIZE){
    tail_->val[tail_->last] = val;
    tail_->last++, size_++;
  }
  //case 3: head item is full
  else{
    Item* temp = new Item();
    tail_->next = temp;
    temp->prev = tail_;
    tail_ = temp;

    tail_->val[0] = val;
    tail_->first=0, tail_->last++, size_++;
  }
}

void ULListStr::pop_back(){
  //case 1: nothing in ulliststr
  if(tail_ == nullptr) return;

  //if there are remaining strings change the value of tail
  else if(tail_->last > tail_->first + 1){
    tail_->val[--tail_->last] = "";
  }
  //if theres no remimaintg strings after deletion
  else{
    Item* temp = tail_;
    tail_ = tail_->prev;
    if(tail_ != NULL){
      tail_->next = nullptr;
      temp->prev = nullptr;
    }else{
      head_ = nullptr, tail_= nullptr;
    }
    delete temp;
  }
  size_--;
}

void ULListStr::push_front(const std::string& val){
  //case 1: create new item
  if(size_ == 0){
    head_ = new Item();
    tail_ = head_;
    head_->first = ARRSIZE - 1, head_->last = ARRSIZE, size_++;
    head_->val[head_->first] = val;
  }
  //case 2: 
  else if(head_->first > 0){
    head_->val[--head_->first] = val;
    size_++;
  }
  //case 3: head item is full
  else{
    Item* temp = new Item();
    temp->next = head_;
    head_->prev = temp;
    head_ = temp;

    head_->first = ARRSIZE - 1, head_->last =  ARRSIZE, size_++;
    head_->val[head_->first] = val;
  }
}

void ULListStr::pop_front(){

  //case 1:  nothing in ulliststr
  if(head_==nullptr){
    return;
  }
  //case 2: if remaining strings after deleteion
  else if(head_->first < head_->last - 1){
    head_->val[head_->first] = "";
    head_->first++;
  }
  //if no remaining strings after deletion, delete
  else{
    Item* temp = head_;
    head_ = head_->next;
    if(head_){
      head_->prev = nullptr;
      temp->next = nullptr;
    }else{
      head_= nullptr, tail_=nullptr;
    }
    delete temp;
  }
  size_--;
}

std::string const & ULListStr::back() const{
  if(size_ == 0){
    throw std::out_of_range("List is empty");
  }
  return tail_->val[tail_->last-1];
}

std::string const & ULListStr::front() const{
  if(size_ == 0){
    throw std::out_of_range("List is empty");
  }
  return head_->val[head_->first];
}

std::string* ULListStr::getValAtLoc(size_t loc) const{
  Item* curr = head_;
  size_t count = 0;
  while(curr){
    size_t numStrings = curr->last - curr->first;
    if(count + numStrings > loc){
      return &curr->val[curr->first+ (loc-count)];

    }

    count+=numStrings;
    curr= curr->next;
  }

  return nullptr;

}