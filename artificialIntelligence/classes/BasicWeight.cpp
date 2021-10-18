#ifndef BASIC_WEIGHT
#define BASIC_WEIGHT

#include <iostream>

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
   this->generate (fl, fw, fh, sl, sw, sh);
}

template <typename T>
BasicWeight<T>::BasicWeight (){
   this->weights = nullptr;
   this->right = nullptr;
   this->back = nullptr;
   this->down = nullptr;
}

template <typename T>
void BasicWeight<T>::print () {
   int total = this->print (0,0,0);
}

template <typename T>
int BasicWeight<T>::print (int length, int width, int height) {
   if (this->down == nullptr) {
      if (this->back == nullptr) {
         if (this->right == nullptr){
            std::cout << "Weight Location: [" << length << "][" << width << "][" << height << "]\n";
            if (this->weights != nullptr) {
               this->weights->printMatrix(); 
            } else {
               std::cout << "No weights found!\n";
            }
            return 1;
         } else {
            std::cout << "Weight Location: [" << length << "][" << width << "][" << height << "]\n";
            if (this->weights != nullptr) {
               this->weights->printMatrix(); 
            } else {
               std::cout << "No weights found!\n";
            }
            return this->right->print (length + 1, width, height) + 1;
         }
      } else {
         std::cout << "Weight Location: [" << length << "][" << width << "][" << height << "]\n";
         if (this->weights != nullptr) {
            this->weights->printMatrix(); 
         } else {
            std::cout << "No weights found!\n";
         }
         return this->back->print (length, width + 1, height) + 1;
      }
   } else {
      std::cout << "Weight Location: [" << length << "][" << width << "][" << height << "]\n";
      if (this->weights != nullptr) {
         this->weights->printMatrix(); 
      } else {
         std::cout << "No weights found!\n";
      }
      return this->down->print (length, width, height + 1) + 1;
   }
}

template <typename T>
void BasicWeight<T>::add (int length, int width, int height, Matrix3D<T>* weights) {
   if (length == 0) {
      if (width == 0) {
         if (height == 0){
            this->weights = weights;
            return this;
         } else {
            this->down = this->down->add (length, width, height - 1, weights);
         }
      } else {
         this->back = this->back->add (length, width - 1, height, weights);
      }
   } else {
      this->right = this->right->add (length - 1, width, height, weights);
   }
   // if (this->root == nullptr) {
   //    this->root = new BasicWeight (layer, weights);
   // } else {
   //    this->root = this->root->add(layer, weights);
   // }
}

template <typename T>
void BasicWeight<T>::addNew (int length, int width, int height) {
   Matrix3D<T>* layer = new Matrix3D<T> (length, width, height);
   layer->randomize ();
   return this->add (length, width, height, weights);
}

template <typename T>
void BasicWeight<T>::generate (int fl, int fw, int fh, int sl, int sw, int sh) {
   Matrix3D<T>* weights = new Matrix3D<T> (sl, sw, sh);
   weights->randomize();
   this->weights = weights;
   
   if (fl > 1) {
      this->right = new BasicWeight<T>();
      this->right->generate (fl - 1, fw, fh, sl, sw, sh);
   }
   if (fw > 1) {
      this->back = new BasicWeight<T>();
      this->back->generate (fl, fw - 1, fh, sl, sw, sh);
   }
   if (fh > 1) {
      this->down = new BasicWeight<T>();
      this->down->generate (fl, fw, fh - 1, sl, sw, sh);
   }
}

template <typename T>
Matrix3D<T>* BasicWeight<T>::getWeightMatrix (int length, int width, int height) {
   if (length == 0) {
      if (width == 0) {
         if (height == 0){
            return this->getWeightMatrix ();
         } else {
            return this->down->getWeightMatrix (length, width, height - 1);
         }
      } else {
         return this->back->getWeightMatrix (length, width - 1, height);
      }
   } else {
      return this->right->getWeightMatrix (length - 1, width, height);
   }
}

template <typename T>
Matrix3D<T>* BasicWeight<T>::getWeightMatrix () {
   return this->weights;
}

#endif