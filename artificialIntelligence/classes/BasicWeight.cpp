#ifndef BASIC_WEIGHT
#define BASIC_WEIGHT

#include <iostream>
#include <string>

#include <coreutils/classes/matrixes/Matrix3D.cpp>

#include <artificialIntelligence/classes/BasicWeight.hpp>

using namespace coreutils::classes::matrixes;
using namespace artificialIntelligence::classes;

template <typename T>
BasicWeight<T>::BasicWeight (Matrix3D<T>* weights){
   this->weights = weights;
   this->right = nullptr;
   this->back = nullptr;
   this->down = nullptr;
}

template <typename T>
BasicWeight<T>::BasicWeight (int fl, int fw, int fh, int sl, int sw, int sh) {
   this->weights = nullptr;
   this->right = nullptr;
   this->back = nullptr;
   this->down = nullptr;
   try {
      if (fl < 1 || fw < 1 || fh < 1 || sl < 1 || sw < 1 || sh < 1) {
         std::cout << " \nfl :: " << fl << " fw :: " << fw << " fh :: " << fh 
                  << " sl :: " << sl << " sw :: " << sw << " sh :: " << sh;
         throw std::invalid_argument("\nBasicWeight generate values are invalid\n\n");
      }
   } catch(const std::invalid_argument& e) {
      std::cout << e.what();
      exit (0);
   };
   this->generate (fl, fw, fh, sl, sw, sh);
   // std::cout << "\n\n" << std::to_string(this->generate (fl, fw, fh, sl, sw, sh) + 1) << "\n\n";
}

template <typename T>
BasicWeight<T>::BasicWeight (){
   this->weights = nullptr;
   this->right = nullptr;
   this->back = nullptr;
   this->down = nullptr;
}

template <typename T>
BasicWeight<T>::~BasicWeight(){
   // needs to traverse through all of the down, and then all of the back, and then all of the right, without repeating
   if (this->weights != nullptr) {
      delete this->weights;
   } else {
      return;
   }

   if (this->right != nullptr) {
      delete this->right;
   } 
   if (this->back != nullptr) {
      delete this->back;
   } 
   if (this->down != nullptr){
      delete this->down;
   }
}

template <typename T>
void BasicWeight<T>::print () {
   int total = this->print (0,0,0);
}

template <typename T>
int BasicWeight<T>::print (int length, int width, int height) {
   // needs to traverse through all of the down, and then all of the back, and then all of the right, without repeating
   if (this->weights != nullptr) {
      std::cout << "Weight Location: [" << length << "][" << width << "][" << height << "]\n";
      this->weights->printMatrix(); 
   } else {
      return 1;
      std::cout << "No weights found!\n";
   }

   int depth = 0;
   if (this->right != nullptr && width == 0 && height == 0) {
      depth += this->right->print (length + 1, width, height) + 1;
   } 
   if (this->back != nullptr && height == 0) {
      depth += this->back->print (length, width + 1, height) + 1;
   } 

   if (this->down != nullptr){
      depth += this->down->print (length, width, height + 1) + 1;
   }
   return depth;
}

template <typename T>
BasicWeight<T> BasicWeight<T>::add (int length, int width, int height, Matrix3D<T>* weights) {
   if (length == 0) {
      if (width == 0) {
         if (height == 0){
            this->weights = weights;
            return this;
         } else {
            this->down = this->down->add (length, width, height - 1, weights);
            return this;
         }
      } else {
         this->back = this->back->add (length, width - 1, height, weights);
         return this;
      }
   } else {
      this->right = this->right->add (length - 1, width, height, weights);
      return this;
   }
}

template <typename T>
BasicWeight<T> BasicWeight<T>::addNew (int length, int width, int height) {
   Matrix3D<T>* layer = new Matrix3D<T> (length, width, height);
   layer->randomize ();
   return this->add (length, width, height, weights);
}

// broken
template <typename T>
int BasicWeight<T>::generate (int fl, int fw, int fh, int sl, int sw, int sh) {
   int i = 0;
   // std::cout << fl << " " << fw << " " << fh << " " << sl << " " << sw << " " << sh << '\n';
      // exit (0);
   Matrix3D<T>* weights = new Matrix3D<T> (sl, sw, sh);
   weights->randomize();
   
   this->weights = weights;
   if (fl > 1 && fw >= 1 && fh >= 1) {
      this->right = new BasicWeight<T>();
      i += this->right->generate (fl - 1, fw, fh, sl, sw, sh) + 1;
   }
   if (fw > 1 && fh >= 1) {
      this->back = new BasicWeight<T>();
      i += this->back->generate (1, fw - 1, fh, sl, sw, sh) + 1;
   }
   if (fh > 1) {
      this->down = new BasicWeight<T>();
      i += this->down->generate (1, 1, fh - 1, sl, sw, sh) + 1;
   }
   return i;
}

template <typename T>
Matrix3D<T>* BasicWeight<T>::getWeightMatrix (int length, int width, int height) {
   if (length == 0) {
      if (width == 0) {
         if (height == 0){
            return this->getWeightMatrix ();
         } else {
            if (this->down == nullptr) {
               return nullptr;
            }
            return this->down->getWeightMatrix (length, width, height - 1);
         }
      } else {
         if (this->back == nullptr) {
            return nullptr;
         }
         return this->back->getWeightMatrix (length, width - 1, height);
      }
   } else {
      if (this->right == nullptr) {
         return nullptr;
      }
      return this->right->getWeightMatrix (length - 1, width, height);
   }
}

template <typename T>
Matrix3D<T>* BasicWeight<T>::getWeightMatrix () {
   return this->weights;
}

template <typename T>
T* BasicWeight<T>::getData (int fl, int fw, int fh, int sl, int sw, int sh) {
   Matrix3D<T>* weights = this->getWeightMatrix(fl, fw, fh);
   if (weights == nullptr) {
      return nullptr;
   }
   return weights->getData(sl, sw, sh);
}

template <typename T>
void BasicWeight<T>::insert (T data, int fl, int fw, int fh, int sl, int sw, int sh) {
   Matrix3D<T>* weights = this->getWeightMatrix(fl, fw, fh);
   if (weights == nullptr) {
      return;
   }
   weights->insert(data, sl, sw, sh);
}

#endif