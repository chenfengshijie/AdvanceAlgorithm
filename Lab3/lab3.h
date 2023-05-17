#pragma once
/**
 * @file skiplist.h
 * @brief SkipList ���ݽṹ��������ʵ��
 * @author chen feng
 * @date 2023-04-29
 */

/**
 * @class Node
 * @brief ����ڵ���
 *
 * ����ڵ�������˽ڵ�ļ���ָ�������ڵ��ָ�롣
 */
#include <iostream>
#include <cstdlib>
#include<iostream>
#include <vector>
#include <bitset>
#include <functional>
using std::vector;
using std::cout;
using std::endl;
// * ����������ĳ������ݽṹ��ʵ�֣�Ϊʵ�����ĵ�һ����Ŀ

template <typename T>
class Node
{
public:
    T key;                  ///< �ڵ�ļ�
    vector<Node *> forward; ///< ָ�������ڵ��ָ������

    /**
     * @brief ����һ���µ�����ڵ�
     * @param key �ڵ�ļ�
     * @param level �ڵ�Ĳ���
     */
    Node(const T &key, int level) : key(key), forward(level + 1, nullptr){};
};

/**
 * @class SkipList
 * @brief �������ݽṹ��
 *
 * �������ṩ�˲��롢ɾ������������ʾ����Ĺ��ܡ�
 */
template <typename T>
class SkipList
{
public:
    /**
     * @brief ����һ���µ�����ʵ��
     * @param max_level ���������������
     * @param p ����ȷ���½ڵ�����ĸ���
     */
    SkipList(int max_level, float p);

    /**
     * @brief ��������ʵ��
     */
    ~SkipList();

    /**
     * @brief ������ɽڵ����
     * @return ����������ɵĽڵ����
     */
    int random_level();

    /**
     * @brief ����һ���µĽڵ�
     * @param key �ڵ�ļ�
     * @param level �ڵ�Ĳ���
     * @return �����´����Ľڵ�ָ��
     */
    Node<T> *create_node(const T &key, int level);

    /**
     * @brief �������в���һ���µĽڵ�
     * @param key Ҫ����Ľڵ�ļ�
     */
    void insert(const T &key);

    /**
     * @brief ��������ɾ��һ���ڵ�
     * @param key Ҫɾ���Ľڵ�ļ�
     */
    void delete_key(const T &key);

    /**
     * @brief ������������һ���ڵ�
     * @param key Ҫ�����Ľڵ�ļ�
     * @return ����ҵ��ڵ㣬���� true�����򷵻� false
     */
    bool search(const T &key);

    /**
     * @brief ��ʾ���������
     */
    void display();

private:
    int max_level;   ///< ���������������
    float p;         ///< ����ȷ���½ڵ�����ĸ���
    int level;       ///< ��ǰ����Ĳ���
    Node<T> *header; ///< �����ͷ�ڵ�
};

// �����캯��
template <typename T>
SkipList<T>::SkipList(int max_level, float p) : max_level(max_level), p(p), level(0)
{
    header = new Node<T>(T(), max_level);
}

// ������������
template <typename T>
SkipList<T>::~SkipList()
{
    delete header;
}

// ������ɽڵ����
template <typename T>
int SkipList<T>::random_level()
{
    float r = static_cast<float>(rand()) / RAND_MAX;
    int lvl = 0;
    while (r < p && lvl < max_level)
    {
        lvl++;
        r = static_cast<float>(rand()) / RAND_MAX;
    }
    return lvl;
}

// ����һ���ڵ�
template <typename T>
Node<T> *SkipList<T>::create_node(const T &key, int level)
{
    return new Node<T>(key, level);
}

// ����ڵ�
template <typename T>
void SkipList<T>::insert(const T &key)
{
    vector<Node<T> *> update(max_level + 1);
    Node<T> *x = header;

    for (int i = level; i >= 0; i--)
    {
        while (x->forward[i] != nullptr && x->forward[i]->key < key)
        {
            x = x->forward[i];
        }
        update[i] = x;
    }

    int new_level = random_level();

    if (new_level > level)
    {
        for (int i = level + 1; i <= new_level; i++)
        {
            update[i] = header;
        }
        level = new_level;
    }

    x = create_node(key, new_level);

    for (int i = 0; i <= new_level; i++)
    {
        x->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = x;
    }
}

// ɾ���ڵ�
template <typename T>
void SkipList<T>::delete_key(const T &key)
{
    vector<Node<T> *> update(max_level + 1);
    Node<T> *x = header;

    for (int i = level; i >= 0; i--)
    {
        while (x->forward[i] != nullptr && x->forward[i]->key < key)
        {
            x = x->forward[i];
        }
        update[i] = x;
    }

    x = x->forward[0];
    if (x->key == key)
    {
        for (int i = 0; i <= level; i++)
        {
            if (update[i]->forward[i] != x)
            {
                break;
            }
            update[i]->forward[i] = x->forward[i];
        }

        delete x;

        while (level > 0 && header->forward[level] == nullptr)
        {
            level--;
        }
    }
}
/**
 * @brief search a particular element
 *
 * @tparam T val_type
 * @param key element_key
 * @return true found
 * @return false Not found
 */
template <typename T>
bool SkipList<T>::search(const T &key)
{
    Node<T> *x = header;
    for (int i = level; i >= 0; i--)
    {
        while (x->forward[i] != nullptr && x->forward[i]->key < key)
        {
            x = x->forward[i];
        }
    }

    x = x->forward[0];

    return x != nullptr && x->key == key; // ��ʾ����
}

template <typename T>
void SkipList<T>::display()
{
    for (int i = 0; i <= level; i++)
    {
        Node<T> *x = header->forward[i];
        cout << "Level " << i << ": ";
        while (x != nullptr)
        {
            cout << x->key << " ";
            x = x->forward[i];
        }
        cout << endl;
    }
}

// * ������ʵ�����ڶ�����ĿBloom Filter��ʵ��

const int BITSET_SIZE = 10000; // λ���鳤��
const int HASH_NUM = 5;        // ��ϣ��������

class BloomFilter
{
public:
    BloomFilter()
    {
        bitset_.reset(); // ��ʼ��λ���飬ȫ����Ϊ0
    }
    /**
     * @brief add elements
     *
     * @param key the key need to be added
     */
    void add(int key)
    {
        for (int i = 0; i < HASH_NUM; i++)
        {
            uint32_t hash_value = std::hash<int>{}(key + i); // ʹ�� std::hash ���ɹ�ϣֵ
            uint32_t index = hash_value % BITSET_SIZE;
            bitset_.set(index); // ����Ӧ��λ����λ����Ϊ1
        }
    }
    /**
     * @brief whether contain a specific key
     *
     * @param key a key
     * @return true Found
     * @return false Not found
     */
    bool contains(int key) const
    {
        for (int i = 0; i < HASH_NUM; i++)
        {
            uint32_t hash_value = std::hash<int>{}(key + i); // ʹ�� std::hash ���ɹ�ϣֵ
            uint32_t index = hash_value % BITSET_SIZE;
            if (!bitset_.test(index))
            { // ���������һ��λ��Ϊ0�����ʾԪ�ز������ڼ�����
                return false;
            }
        }
        return true; // ����λ�ö�Ϊ1�����ʾԪ�ؿ��ܴ����ڼ�����
    }

private:
    // the bit array
    std::bitset<BITSET_SIZE> bitset_;
};

//
