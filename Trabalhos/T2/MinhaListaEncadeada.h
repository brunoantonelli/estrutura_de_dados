#ifndef DEC0006_MINHA_LISTA_ENCADEADA_H
#define DEC0006_MINHA_LISTA_ENCADEADA_H

#include <cstddef>
// std::size_t

#include "Elemento.h"
// Elemento
#include "ListaEncadeadaAbstrata.h"
#include "excecoes.h"
// ExcecaoDadoInexistente
// ExcecaoListaEncadeadaVazia
// ExcecaoNaoImplementado
// ExcecaoPosicaoInvalida

/**
 * @brief Uma lista encadeada de dados.
 * 
 * @tparam T O tipo dos dados armazenados na lista.
 */
template<typename T>


class MinhaListaEncadeada: public ListaEncadeadaAbstrata<T>
{
    public:
   
    MinhaListaEncadeada()
    {
      this ->_primeiro = NULL;
      this ->_tamanho  = 0;
    }

  ~MinhaListaEncadeada()
  {
    Elemento<T> *Proximo_Elemento = NULL;
    Elemento<T> *Elemento_Auxiliar = this ->_primeiro;

    while (Elemento_Auxiliar != NULL)
    {
      Proximo_Elemento = Elemento_Auxiliar ->proximo;
      delete Elemento_Auxiliar;
      Elemento_Auxiliar = Proximo_Elemento;

    }
  };

  std::size_t tamanho() const
 { 
    int count = 0;
    Elemento<T> *atual = this->_primeiro;
    if (atual == NULL){
        return count;
    }
    else{
      while (atual != NULL)
      {
        atual = atual->proximo;
        count++;
      }
      
    }
    return count;
  };

  bool vazia() const
 {
    if ( (this->_primeiro == NULL))
    {
      return true;
    }
    else
    {
      return false;
    }   
  };

  std::size_t posicao(T dado) const
 {
    if(this->_tamanho == 0)
    {
      throw ExcecaoListaEncadeadaVazia();
    }
    else
    {
      Elemento<T> *Elemento_Auxiliar = this->_primeiro;
      size_t indice = 0;
      while (Elemento_Auxiliar != NULL){
        if(dado == Elemento_Auxiliar->dado)
        {
          return indice;
        }
        indice++;
        Elemento_Auxiliar = Elemento_Auxiliar->proximo;
      }
      if(Elemento_Auxiliar == NULL){
        throw ExcecaoDadoInexistente();
      } 
      return 0;
    }
  };

  bool contem(T dado) const
 {
      Elemento<T> *Elemento_Atual = (this ->_primeiro);
        while (Elemento_Atual != NULL)
        {
          if (Elemento_Atual ->dado == dado)
          {
           return true;
          }
          Elemento_Atual = Elemento_Atual ->proximo;
        }
      return false;   
  }
  void inserirNoInicio(T dado)
  {
    Elemento<T> *Novo_Elemento = new Elemento<T>(dado,nullptr);
    Novo_Elemento->proximo = this->_primeiro;
    this->_primeiro = Novo_Elemento;
    this->_tamanho++;
  };
  
  void inserir(size_t posicao, T dado)
  {
    if(posicao == 0 and tamanho() >= 0)
    {
      inserirNoInicio(dado);
    }
    else if (posicao < 0 or posicao > tamanho())
    {
      throw ExcecaoPosicaoInvalida();
    }
    else if(posicao == tamanho())
    {
      inserirNoFim(dado);
    }
    else
    {
      int auxiliar = 0;
      Elemento<T> *Elemento_Auxiliar = this->_primeiro;
      while (auxiliar < posicao - 1 and Elemento_Auxiliar->proximo != NULL and Elemento_Auxiliar != NULL)
      {
        Elemento_Auxiliar = Elemento_Auxiliar->proximo;
        auxiliar++;
      }
      Elemento<T> *Novo_Elemento = new Elemento<T>(dado, nullptr);
      Novo_Elemento->proximo = Elemento_Auxiliar->proximo;
      Elemento_Auxiliar->proximo = Novo_Elemento;
      this->_tamanho++;
    }
    return; 
  };

  void inserirNoFim(T dado)
  {
    if (this->_primeiro == NULL)
    {
      inserirNoInicio(dado);
     return;
    } 
   else
  {
    Elemento<T> *Novo_Elemento = new Elemento<T>(dado, nullptr);
    Novo_Elemento->proximo=NULL;
    Elemento<T> *Ultimo_Elemento = this->_primeiro;
    while (Ultimo_Elemento->proximo != NULL)
    {
      Ultimo_Elemento = Ultimo_Elemento->proximo;
    }
    Ultimo_Elemento->proximo = Novo_Elemento;
    this->_tamanho++;
    return;
  }
  };

  T removerDoInicio()
  {
    if (this->_tamanho == 0)
    {
      throw ExcecaoListaEncadeadaVazia();
    }
    else
    {
      Elemento<T> *Elemento_Auxiliar = this->_primeiro;
      T dado_Auxiliar = Elemento_Auxiliar->dado;
      this->_primeiro = this ->_primeiro->proximo;
      delete Elemento_Auxiliar;
      this->_tamanho--;
      return dado_Auxiliar;
    }
  };

  T removerDe(size_t posicao)
  {
    if (vazia())
    {
      throw ExcecaoPosicaoInvalida();
    }
    else if(posicao < 0 or posicao >= tamanho())
    {
      throw ExcecaoPosicaoInvalida();
    }
    else if (posicao == 0)
    {
      return removerDoInicio();
    }
    else
    {
      Elemento<T> *Elemento_Auxiliar = this->_primeiro;
      for (size_t i = 0; Elemento_Auxiliar != NULL and i < posicao-1; i++)
      {
        Elemento_Auxiliar = Elemento_Auxiliar->proximo;
      }
      if (Elemento_Auxiliar->proximo->proximo == NULL)
      {
        return removerDoFim();
      }
      else if (Elemento_Auxiliar != NULL or Elemento_Auxiliar->proximo != NULL)
      {
        Elemento<T> *Elemento_Deletar = Elemento_Auxiliar->proximo;
        Elemento_Auxiliar->proximo = Elemento_Auxiliar->proximo->proximo;
        T auxiliar = Elemento_Deletar->dado;
        delete Elemento_Deletar;
        this->_tamanho--;
        return auxiliar;
      }
      
    }
    return 0;
  };
 
  T removerDoFim()
  {
    Elemento<T> *Elemento_Auxiliar = this->_primeiro;
    if (this->_primeiro == NULL)
    {
      throw ExcecaoListaEncadeadaVazia();
    }
    else if (Elemento_Auxiliar->proximo == NULL)
    {
      return removerDoInicio();
    }
    else
    {
      while (Elemento_Auxiliar->proximo->proximo != NULL)
      {
        Elemento_Auxiliar = Elemento_Auxiliar->proximo;
      }
      Elemento<T> *ultimo_Elemento = Elemento_Auxiliar->proximo;
      T Dado_Removido = ultimo_Elemento->dado;
      delete ultimo_Elemento;
      Elemento_Auxiliar->proximo = NULL;
      this->_tamanho--;
      return Dado_Removido;
    }
    return 0;
  };
  
  void remover(T dado)
  {
    if(this->_primeiro == NULL)
    {
      throw ExcecaoListaEncadeadaVazia();
    }
    else if(contem(dado) == false)
    {
      throw ExcecaoDadoInexistente();
    }
    else{
      size_t indice = posicao(dado);
      removerDe(indice);
    } 
  };
};

#endif