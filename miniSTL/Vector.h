//
// Created by Administrator on 2022/10/26.
//

#ifndef MINISTL_VECTOR_H
#define MINISTL_VECTOR_H

#include "iostream"
#include "exception"

namespace miniSTL {
    template<class T>
    class Vector {
    public:
        using pointer = T *;
        using const_pointer = const T *;
        using value_type = T;
        using size_type = size_t;

        Vector() noexcept {

        }

        Vector(size_t _n) noexcept {
            __start = new value_type[_n];
            __finish = __start + _n;
            __end_of_storage = __start + _n;
        }

        Vector(size_t _n, value_type _data) noexcept {
            __start = new value_type[_n];
            __finish = __start;
            __end_of_storage = __start + _n;
            while (__finish != __end_of_storage) {
                *__finish = value_type(std::forward<value_type>>
                (_data));
                __finish++;
            }
        }

        Vector(Vector &_v) noexcept {
            __start = new value_type[_v.capacity()];
            for (int i = 0; i < _v.size(); i++) {
                *__finish = value_type(std::forward<value_type>(*(_v.__start + i)));
                __finish++;
            }
        }

        Vector(Vector &&_v) noexcept {
            __start = _v.__start;
            __finish = _v.__finish;
            __end_of_storage = _v.__end_of_storage;
        }

        void reserve(size_type _n) {
            if (_n <= size()) {
                return;
            }
            pointer ptr = __start;
            size_type n = size();
            __start = new value_type[_n];
            __finish = __start;
            __end_of_storage = __start + _n;
            for (int i = 0; i < n; i++) {
                *__finish = value_type(std::forward<value_type>(*(ptr + i)));
                __finish++;
            }
            if (ptr != nullptr) {
                delete[] ptr;
            }
        }

        void push_back(value_type &_x) noexcept {
            if (__finish == __end_of_storage) {
                size_type n = size() > 0 ? 2 * size() : 1;
                reserve(n);
            }
            *__finish = value_type(std::forward<value_type>(_x));
            __finish++;
        }

        void push_back(value_type &&_x) noexcept {
            if (__finish == __end_of_storage) {
                size_type n = size() > 0 ? 2 * size() : 1;
                reserve(n);
            }
            *__finish = value_type(std::forward<value_type>(_x));
            __finish++;
        }


        void pop_back() {
            if (size() == 0) {
                throw std::out_of_range("there are no elements can pop");
            }
            __finish--;
        }

        size_type size() const noexcept {
            if (__start == __finish) {
                return 0;
            }
            return __finish - __start;
        }

        value_type at(size_type _n) {
            if (_n >= size()) {
                throw std::out_of_range("the index is more than the scope of the size");
            }
            return *(__finish + _n);
        }

        pointer begin() const noexcept {
            return __start;
        }

        pointer end() const noexcept {
            return __finish;
        }

        value_type front() {
            return *__start;
        }

        value_type back() {
            return *(__finish - 1);
        }

        size_type capacity() const noexcept {
            if (__start == __end_of_storage) {
                return 0;
            }
            return __end_of_storage - __start;
        }

        void resize(size_type _n) noexcept {
            if (_n > capacity()) {
                reserve(_n);
            } else if (_n > size()) {
                while (__finish != __start + _n) {
                    value_type _t;
                    *__finish = value_type(std::forward<value_type>(_t));
                    __finish++;
                }
            } else {
                while (__finish != __start + _n) {
                    __finish--;
                }
            }
        }

        void resize(size_type _n, value_type _t) noexcept {
            if (_n > capacity()) {
                reserve(_n);
            } else if (_n > size()) {
                while (__finish != __start + _n) {
                    *__finish = value_type(std::forward<value_type>(_t));
                    __finish++;
                }
            } else {
                while (__finish != __start + _n) {
                    __finish--;
                }
            }
        }

        bool empty() {
            return size() == 0;
        }

        value_type &operator[](size_type _n) {
            if (_n >= size()) {
                throw std::out_of_range("the index is more than the scope of the size");
            }
            return *(__start + _n);
        }

        pointer insert(size_type _n, value_type &_x) {
            if (__finish == __end_of_storage) {
                size_type n = capacity() > 0 ? 2 * capacity() : 1;
                reserve(n);
            }
            __finish++;
            pointer _t = __finish - 1;
            while (_t != __start + _n) {
                *_t = value_type(std::forward<value_type>(*(_t - 1)));
                _t--;
            }
            *_t = value_type(std::forward<value_type>(_x));
            return _t;
        }

        pointer insert(size_type _n, value_type &&_x) {
            if (__finish == __end_of_storage) {
                size_type n = capacity() > 0 ? 2 * capacity() : 1;
                reserve(n);
            }
            __finish++;
            pointer _t = __finish--;
            while (_t != __start + _n) {
                *_t = value_type(std::forward<value_type>(*(_t - 1)));
                _t--;
            }
            *_t = value_type(std::forward<value_type>(_x));
            return _t;
        }

        pointer insert(size_type _n, size_type _c, value_type &_x) {
            while (size() + _c >= capacity()) {
                size_type n = capacity() > 0 ? 2 * capacity() : 1;
                reserve(n);
            }
            __finish += _c;
            pointer _t = __finish - 1;
            while (_t != __start + _n + _c - 1) {
                *_t = value_type(std::forward<value_type>(*(_t - _c)));
                _t--;
            }
            while (_t != __start + _n) {
                *_t = value_type(std::forward<value_type>(_x));
                _t--;
            }
            *_t = value_type(std::forward<value_type>(_x));
            return _t;
        }

        pointer insert(size_type _n, size_type _c, value_type &&_x) {
            if (_n >= size()) {
                throw std::out_of_range("the index is more than the scope of the size");
            }
            while (size() + _c >= capacity()) {
                size_type n = capacity() > 0 ? 2 * capacity() : 1;
                reserve(n);
            }
            __finish += _c;
            pointer _t = __finish - 1;
            while (_t != __start + _n + _c - 1) {
                *_t = value_type(std::forward<value_type>(*(_t - _c)));
                _t--;
            }
            while (_t != __start + _n) {
                *_t = value_type(std::forward<value_type>(_x));
                _t--;
            }
            *_t = value_type(std::forward<value_type>(_x));
            return _t;
        }

        pointer erase(size_type _n) {
            if (_n >= size()) {
                throw std::out_of_range("the index is more than the scope of the size");
            }
            pointer _t = __start + _n;
            __finish--;
            while (_t != __finish) {
                *_t = value_type(std::forward<value_type>(*(_t + 1)));
                _t++;
            }
            return __start + _n;
        }

        void clear() {
            delete __start;
            __start = nullptr;
            __finish = nullptr;
            __end_of_storage = nullptr;
        }

    private:
        pointer __start = nullptr;
        pointer __finish = nullptr;
        pointer __end_of_storage = nullptr;

    };
}
#endif //MINISTL_VECTOR_H
