#pragma once

namespace Nebula
{
    template<typename T>
    class ObjectPool
    {
        //deal with problem when right most one is first in stack, and poping it result in huge size fallback.
        //maybe use a vector for stack, and do binary search insert.
        
        private:
            
            int size, maxSize;
            std::stack<int> nextAvailableStack;
            std::vector<bool> isAvailable;
            std::vector<T> data;
            
        public:
            
            ObjectPool(){
                
            };
            virtual ~ObjectPool(){
                
            };
            
            void create(int maxSize){
                this->maxSize = maxSize;
                
                this->size = 0;
                
                this->isAvailable.clear();
                this->isAvailable.reserve(maxSize);
                this->data.clear();
                this->data.reserve(maxSize);
                
                for (int i = maxSize-1; i >= 0; i--){
                    this->nextAvailableStack.push(i);
                }
                for (int i = 0; i < maxSize; i++){
                    this->isAvailable.push_back(true);
                    this->data.push_back(T());
                    this->data[i].poolIndex = i;
                }
            };
            
            void clear(){
                this->size = 0;
                
                while(this->nextAvailableStack.size()) this->nextAvailableStack.pop();
                for (int i = this->maxSize-1; i >= 0; i--){
                    this->nextAvailableStack.push(i);
                }
                for (int i = 0; i < this->maxSize; i++){
                    this->isAvailable[i] = true;
                }
            };
            
            T& operator [] (uint i){
                return data[i];
            };
            
            void disable(int index){
                if (!this->isAvailable[index]){
                    this->isAvailable[index] = true;
                    this->nextAvailableStack.push(index);
                    if (index == this->size - 1){
                        while (this->size && this->isAvailable[this->size - 1]) this->size--;
                    }
                }
            };
            int enableNext(){
                if (!this->nextAvailableStack.size()) return -1;
                int next = this->nextAvailableStack.top();
                this->isAvailable[next] = false;
                this->nextAvailableStack.pop();
                this->size = std::max(this->size, next + 1);
                return next;
            }; //-1 if none
            bool isEnabled(int index){
                return !this->isAvailable[index];
            };
            bool isFull(){
                return !this->nextAvailableStack.size();
            };
            bool isEmpty(){
                return this->nextAvailableStack.size() == this->maxSize;
            };
            
            //getters
            int get_size(){
                return this->size;
            };
            int get_maxSize(){
                return this->maxSize;
            };
            
            //setters

    };
}
