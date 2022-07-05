#ifndef MINHA_ARVORE_DE_BUSCA_BINARIA_HPP
#define MINHA_ARVORE_DE_BUSCA_BINARIA_HPP

#include "ArvoreDeBuscaBinaria.h"

/**
 * @brief Representa uma árvore binária de busca.
 * 
 * @tparam T O tipo de dado guardado na árvore.
 */
template<typename T>
class MinhaArvoreDeBuscaBinaria : public ArvoreDeBuscaBinaria<T>
{
    protected:
    int getQuantidade(Nodo<T> *chave) const
    {
        if (chave != nullptr)
        {
            return (1 + this->getQuantidade(chave->filhoEsquerda) + this->getQuantidade(chave->filhoDireita));
        }
        return 0;
    }


    void emOrdemAux(Nodo<T> *chave, ListaEncadeadaAbstrata<T> *listaEmOrdem) const
    {
        if (chave != nullptr)
        {
            this->emOrdemAux(chave->filhoEsquerda, listaEmOrdem);
            listaEmOrdem->inserirNoFim(chave->chave);
            this->emOrdemAux(chave->filhoDireita, listaEmOrdem);
        }
        return;
    }

    void preOrdemAux(Nodo<T> *chave, ListaEncadeadaAbstrata<T> *listaPreOrdem) const
    {
        if (chave != nullptr)
        {
            listaPreOrdem->inserirNoFim(chave->chave);
            this->preOrdemAux(chave->filhoEsquerda, listaPreOrdem);
            this->preOrdemAux(chave->filhoDireita, listaPreOrdem);
        }
        return;
    }

    void posOrdemAux(Nodo<T> *chave, ListaEncadeadaAbstrata<T> *listaPosOrdem) const
    {
        if (chave != nullptr)
        {
            this->posOrdemAux(chave->filhoEsquerda, listaPosOrdem);
            this->posOrdemAux(chave->filhoDireita, listaPosOrdem);
            listaPosOrdem->inserirNoFim(chave->chave);
        }
        return;
    }

    
    void insereNaArvore(Nodo<T> *chaveAtual, T novoValor)
    {
        if (this->vazia())
        {
            Nodo<T> *novaChave = new Nodo<T>{novoValor, 0};

            delete this->_raiz;

            this->_raiz = novaChave;

            return;
        }

        if (novoValor < chaveAtual->chave)
        {
            if (chaveAtual->filhoEsquerda == nullptr)
            {
                Nodo<T> *novaChave = new Nodo<T>
                {
                    novoValor, chaveAtual->altura+1
                };

                chaveAtual->filhoEsquerda = novaChave;
            }
            else
            {
                this->insereNaArvore(chaveAtual->filhoEsquerda, novoValor);
            }
        }
        else
        {
            if (chaveAtual->filhoDireita == nullptr)
            {
                Nodo<T> *novaChave = new Nodo<T>{novoValor, chaveAtual->altura+1};

                chaveAtual->filhoDireita = novaChave;
            }
            else
            {
                this->insereNaArvore(chaveAtual->filhoDireita, novoValor);
            }
        }
        return;
    }

    

    Nodo<T> *getContem(T chave, Nodo<T> *raiz) const
    {
        while (raiz != nullptr && raiz->chave != chave)
        {
            if (raiz->chave < chave)
            {
                raiz = raiz->filhoDireita;
            }
            else
            {
                raiz = raiz->filhoEsquerda;
            }
        }
        return raiz; 
    }

    Nodo<T> *getPai(T chave, Nodo<T> *pai) const
    {
        if (pai == nullptr)
        {
            return nullptr;
        }

        if (pai->chave == chave)
        {
            return nullptr;
        }

        if (pai != nullptr && pai->chave != chave)
        {
            if (pai->chave < chave)
            {
                if (pai->filhoDireita->chave != chave)
                {
                    return this->getPai(chave, pai->filhoDireita);
                }
            }

            if (pai->chave > chave)
            {
                if (pai->filhoEsquerda->chave != chave)
                {
                    return this->getPai(chave, pai->filhoEsquerda);
                }
            }
        }
        return pai;
    }

    
    int alturaSubArvore(Nodo<T> *chave) const
    {
        int alturaEsquerda = 0, alturaDireita = 0, altura = 0;

        if (chave->filhoEsquerda != nullptr)
        {
            alturaEsquerda = 1 + alturaSubArvore(chave->filhoEsquerda);
        }

        if (chave->filhoDireita != nullptr)
        {
            alturaDireita = 1 + alturaSubArvore(chave->filhoDireita);
        }

        return checaAltura(alturaEsquerda, alturaDireita, altura);
    }

    int checaAltura(int Esquerda, int Direita, int altura) const
    {
        if (Esquerda >= Direita)
        {
            altura = Esquerda;
            return altura;
        }
        else
        {
            altura = Direita;
            return altura;
        }
    }

    
    T removeDaArvore(T chaveParaRemover, Nodo<T> *chavePai)
    {
        Nodo<T> *chave;

        if (chavePai->chave == chaveParaRemover)
        {
            if (verificaFolha(chavePai))
            {
                T chaveRemovida = chavePai->chave;

                chavePai = nullptr;
                delete chavePai;

                return chaveRemovida;
            }
            chave = chavePai;
        }
        else if (chavePai->filhoEsquerda != nullptr && chavePai->filhoEsquerda->chave == chaveParaRemover)
        {
            chave = chavePai->filhoEsquerda;

            if (verificaFolha(chave))
            {
                T chaveRemovida = chave->chave;

                chavePai->filhoEsquerda = nullptr;
                delete chave;

                return chaveRemovida;
            }
        }
        else if (chavePai->filhoDireita != nullptr && chavePai->filhoDireita->chave == chaveParaRemover)
        {
            chave = chavePai->filhoDireita;

            if (verificaFolha(chave))
            {
                T chaveRemovida = chave->chave;

                chavePai->filhoDireita = nullptr;
                delete chave;

                return chaveRemovida;
            }
        }
        
        if(chave != nullptr && chave->filhoDireita != nullptr)
        {
            Nodo<T> *chaveAux = chave->filhoDireita;
            Nodo<T> *chavePaiAux = chave;

            while (chaveAux->filhoEsquerda != nullptr)
            {
                chavePaiAux = chaveAux;
                chaveAux = chaveAux->filhoEsquerda;
            }

            chave->chave = chaveAux->chave;
            chaveAux->chave = chaveParaRemover;
            return this->removeDaArvore(chaveParaRemover, chavePaiAux);
        }
        return chaveParaRemover;
    }

    bool verificaFolha(Nodo<T> *chave)
    {
        if (chave->filhoEsquerda == nullptr && chave->filhoDireita == nullptr)
        {
            return true;
        }
        return false;
    }


    void destruirArvore(Nodo<T> *chave)
    {
        if (chave != nullptr)
        {
            this->destruirArvore(chave->filhoEsquerda);
            this->destruirArvore(chave->filhoDireita);
            delete chave;
        }
    }
    
    public:
    ~MinhaArvoreDeBuscaBinaria() 
    {
        if (this->_raiz != nullptr)
        {
        this->destruirArvore(this->_raiz);
        }
        return;
    };

    bool vazia() const 
    {
        if (this->quantidade() == 0 || this->_raiz == nullptr)
        {
            return true;
        }
        return false;
    };
    
 
    int quantidade() const 
    {
        int quantidade = 0;

        quantidade = this->getQuantidade(this->_raiz);

        return quantidade;
    };
    
 
    bool contem(T chave) const 
    {    
        if (!this->vazia())
        {
            Nodo<T> *raiz = this->getContem(chave, this->_raiz);

            if (raiz == nullptr)
            {
                return false;
            }

            if (raiz->chave == chave)
            {
                return true;
            }

        }
        return false;
    };
    
    
    std::optional<int> altura(T chave) const 
    {
        if (this->contem(chave))
        {
            Nodo<T> *raiz = this->getContem(chave, this->_raiz);
            return this->alturaSubArvore(raiz);
        }
        return std::nullopt;
    };
       
    void inserir(T chave) 
    {
        return this->insereNaArvore(this->_raiz, chave);
    };

      
    void remover(T chave)
    {
        Nodo<T> *raiz = this->_raiz;


        if(raiz->chave == chave && this->verificaFolha(raiz))
        {
            this->_raiz = nullptr;

            delete raiz;

            return;
        }

        if (this->contem(chave))
        {
            Nodo<T> *chavePai = this->getPai(chave, raiz);
            if (chavePai == nullptr)
            {
                this->removeDaArvore(chave, raiz);
                return;
            }
            this->removeDaArvore(chave, chavePai);
        }
        return;
    };


    std::optional<T> filhoEsquerdaDe(T chave) const 
    {
        if (this->contem(chave))
        {
            Nodo<T> *chavePai = this->getContem(chave, this->_raiz);

            if (chavePai->filhoEsquerda != nullptr)
            {
                return chavePai->filhoEsquerda->chave;
            }
        }
        return std::nullopt;
    };
       
    std::optional<T> filhoDireitaDe(T chave) const 
    {
        if (this->contem(chave))
        {
            Nodo<T> *chavePai = this->getContem(chave, this->_raiz);

            if (chavePai->filhoDireita != nullptr)
            {
                return chavePai->filhoDireita->chave;
            }
        }
        return std::nullopt;
    };

    ListaEncadeadaAbstrata<T>* emOrdem() const 
    {
        ListaEncadeadaAbstrata<T> *listaEmOrdem = new MinhaListaEncadeada<T>();

        this->emOrdemAux(this->_raiz, listaEmOrdem);

       return listaEmOrdem;
    
    };

    ListaEncadeadaAbstrata<T>* preOrdem() const 
    {
        ListaEncadeadaAbstrata<T> *listaPreOrdem = new MinhaListaEncadeada<T>();

        this->preOrdemAux(this->_raiz, listaPreOrdem);

        return listaPreOrdem;
     
    };
    
    ListaEncadeadaAbstrata<T>* posOrdem() const 
    {
        ListaEncadeadaAbstrata<T> *listaPosOrdem = new MinhaListaEncadeada<T>();

        this->posOrdemAux(this->_raiz, listaPosOrdem);

       return listaPosOrdem;
      
    };
};

#endif