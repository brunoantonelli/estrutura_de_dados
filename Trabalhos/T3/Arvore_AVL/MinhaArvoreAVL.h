#ifndef MINHA_ARVORE_AVL_HPP
#define MINHA_ARVORE_AVL_HPP

#include "MinhaArvoreDeBuscaBinaria.h"

/**
 * @brief Representa uma árvore AVL.
 * 
 * @tparam T O tipo de dado guardado na árvore.
 */
template <typename T>
class MinhaArvoreAVL final : public MinhaArvoreDeBuscaBinaria<T>
{
    private:
    
    int getRotacao(Nodo<T> *chave) const 
    {
        int aux = 0, esquerda = 0, direita = 0;

        if (chave != nullptr)
         {
              if (chave->filhoEsquerda != nullptr)
                 {
                    esquerda = chave->filhoEsquerda->altura;
                esquerda = this->alturaSubArvore(chave->filhoEsquerda) + 1;
                 }
              if (chave->filhoDireita != nullptr)
                 {
                direita = this->alturaSubArvore(chave->filhoDireita) + 1;
                 }

            aux = esquerda - direita;

            return aux;
        }
        return 0;
    }

    void balanceiaArvore(Nodo<T> *pai)
    {
        if (pai != nullptr)
        {
            int aux = this->getRotacao(pai);

            // Rotação Simples a Esquerda
            if (aux < -1)
            {
                aux = this->getRotacao(pai->filhoDireita);
                if (aux <= 0)
                {
                    Nodo<T> *avo = this->getPai(pai->chave, this->_raiz);

                    if (avo == nullptr)
                    {
                        this->_raiz = this->RotacaoEsquerdaEsquerda(pai);
                    }
                    else
                    {
                        avo->filhoDireita = this->RotacaoEsquerdaEsquerda(pai);
                    }
                    return;

                }
                else    // Rotação Direita Esquerda
                {
                    Nodo<T> *avo = this->getPai(pai->chave, this->_raiz);

                    if (avo == nullptr)
                    {
                        this->_raiz = this->RotacaoDireitaEsquerda(pai);
                    }
                    else
                    {
                        avo->filhoDireita = this->RotacaoDireitaEsquerda(pai);
                    }

                    return;
                }
            }

            // Rotação Simples a Direita
            if (aux > 1)
            {
                aux = this->getRotacao(pai->filhoEsquerda);
                if (aux >= 0)
                {
                    Nodo<T> *avo = this->getPai(pai->chave, this->_raiz);

                    if (avo == nullptr)
                    {
                        this->_raiz = this->RotacaoDireitaDireita(pai);
                    }
                    else
                    {
                        avo->filhoEsquerda = this->RotacaoDireitaDireita(pai);
                    }
                    return;
                }
                else    // Rotação Esquerda Direita
                {   
                    Nodo<T> *avo = this->getPai(pai->chave, this->_raiz);

                    if (avo == nullptr)
                    {
                        this->_raiz = this->RotacaoEsquerdaDireita(pai);
                    }
                    else
                    {
                        avo->filhoEsquerda = this->RotacaoEsquerdaDireita(pai);
                    }
                    return;
                }
            }

            if (pai->chave == this->_raiz->chave)
            {
                return;
            }
            
            return balanceiaArvore(this->getPai(pai->chave, this->_raiz));
        }
        return;
    }

    Nodo<T> *RotacaoDireitaDireita(Nodo<T> *pai) 
    {
        Nodo<T> *filho      = pai->filhoEsquerda;
        pai->filhoEsquerda  = filho->filhoDireita;
        filho->filhoDireita = pai;

        return filho;
    }

    Nodo<T> *RotacaoEsquerdaEsquerda(Nodo<T> *pai) 
    {
        Nodo<T> *filho       = pai->filhoDireita;
        pai->filhoDireita    = filho->filhoEsquerda;
        filho->filhoEsquerda = pai;

        return filho;
    }

    Nodo<T> *RotacaoDireitaEsquerda(Nodo<T> *pai) 
    {
        pai->filhoDireita = this->RotacaoDireitaDireita(pai->filhoDireita);
        return this->RotacaoEsquerdaEsquerda(pai);
    }

     Nodo<T> *RotacaoEsquerdaDireita(Nodo<T> *pai) 
    {
        pai->filhoEsquerda = this->RotacaoEsquerdaEsquerda(pai->filhoEsquerda);
        return this->RotacaoDireitaDireita(pai);
    }

    
    public:

    void inserir(T chave)
    {
        MinhaArvoreDeBuscaBinaria<T>::inserir(chave);
        Nodo<T> *pai = this->getPai(chave, this->_raiz);
        this->balanceiaArvore(pai);
    }

    void remover(T chave)
    {
        Nodo<T> *pai = this->getPai(chave, this->_raiz);
        MinhaArvoreDeBuscaBinaria<T>::remover(chave);
        this->balanceiaArvore(pai);
    }

};

#endif
