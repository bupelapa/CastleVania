#include "stdafx.h"

template <class TL>
class Lista {
private:
    /* template Node para usar um node da Lista */
    template <class TE>
    class Node {
    private:
        Node<TE>* pProximo;
        Node<TE>* pAnterior;
        TE* pInfo;

    public:
        Node() {
            pProximo = NULL;
            pAnterior = NULL;
            pInfo = NULL;
        }
        ~Node() {
            pProximo = NULL;
            pAnterior = NULL;
            pInfo = NULL;
        }
        /* Set proximo template Node - uso interno */
        void setProximo(Node<TE>* pProximo) { this->pProximo = pProximo; }
        /* proximo node Lista */
        Node<TE>* getProximo() { return pProximo; }
        /* Set node anterior */
        void setAnterior(Node<TE>* pAnterior) { this->pAnterior = pAnterior; }
        /* Get node anterior*/
        Node<TE>* getAnterior() { return pAnterior; }
        /* Seta o pointer para o que o template Node aponta*/
        void setInfo(TE* pInfo) { this->pInfo = pInfo; }
        /* Retorna o ponteiro. */
        TE* getInfo() { return pInfo; }
    };

    Node<TL>* pPrimeiro;
    Node<TL>* pUltimo;


public:
    Lista();
    ~Lista();

    int size;
    void clear();
    void append(TL* pInfo);
    int comprimento() { return size; }
    TL* operator[](int x);
    bool remove(TL* pTL);

private:
    void setNode(Node<TL>* pNode);
    Node<TL>* getpPrimeiro() { return pPrimeiro; }
    Node<TL>* getpUltimo() { return pUltimo; }
};

template <class TL>
Lista<TL>::Lista() :
pPrimeiro(), pUltimo(), size(0) {
    clear();
}

template <class TL>
Lista<TL>::~Lista() {
    clear();
}

/* Deleta a Lista */
template <class TL>
void Lista<TL>::clear() {
    Node<TL>* paux1;
    Node<TL>* paux2;

    paux1 = pPrimeiro;
    paux2 = paux1;

    while (paux1 != NULL) {
        delete (paux1->getInfo());
        paux2 = paux1->getProximo();
        delete (paux1);
        paux1 = paux2;
        size--;
    }

    pPrimeiro = NULL;
    pUltimo = NULL;
}

/* Adiciona um node a Lista - uso interno */
template <class TL>
void Lista<TL>::setNode(Node<TL>* pNode) {
    if (pNode != NULL) {
        if (pPrimeiro == NULL) {
            pPrimeiro = pNode;
            pUltimo = pNode;
        } else {
            pUltimo->setProximo(pNode);
            pNode->setAnterior(pUltimo);
            pUltimo = pNode;
        }
        size++;

    } else {
        std::cout << "ERROR: on Lista<TL>::setNode -> Pointer pNode == NULL. Insert not succeeded." << std::endl;
    }
}

/* Acopla um node Lista */
template <class TL>
void Lista<TL>::append(TL* pInfo) {
    if (pInfo != NULL) {
        Node<TL>* pNode = NULL;
        pNode = new Node<TL>();
        pNode->setInfo(pInfo);
        setNode(pNode);

    } else {
        std::cout << "ERROR: on Lista<TL>::append -> pInfo == NULL" << std::endl;
    }
}

/* Usa um iterador para navegar a lista, retorna o ponteiro  */
template <class TL>
TL* Lista<TL>::operator[](int x) {
    if (x >= size || x < 0) {
        std::cout << "ERROR: Segmentation fault on template Lista. Exceeded boundaries." << std::endl;
        exit(1);
    }

    Node<TL>* pAux = pPrimeiro;
    for (int i = 0; i < x; i++) {
        pAux = pAux->getProximo();
    }

    if (pAux == NULL) {
        cout << "ERROR: on template operator[] pAux == NULL." << endl;
        exit(1);
    }
    return pAux->getInfo();
}

/* Remove um elemento especifico da lista, retorna verdadeiro se fizer */
template <class TL>
bool Lista<TL>::remove(TL* pTL) {
    Node<TL>* pAux = pPrimeiro;
    Node<TL>* pAnte = NULL;
    while (pAux != NULL) {
        if (pAux->getInfo() == pTL) {
            if (pAux == pPrimeiro)
                pPrimeiro = pAux->getProximo();
            else
                pAnte->setProximo(pAux->getProximo());

            //delete (pTL);
            delete (pAux);
            size--;
            return true;
        }
        pAnte = pAux;
        pAux = pAux->getProximo();
    }
    return false;
}

