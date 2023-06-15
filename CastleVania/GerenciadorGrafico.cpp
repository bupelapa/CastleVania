#include "GerenciadorGrafico.hpp"


        GerenciadorGrafico* GerenciadorGrafico::pGrafico = nullptr;

        GerenciadorGrafico::GerenciadorGrafico() :
        window(new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Castlevania++")),
        view(sf::Vector2f(WIDTH / 2, HEIGHT / 2), sf::Vector2f(WIDTH, HEIGHT)),
        mapaTextura() {
         window->setFramerateLimit(FRAME_RATE);
         fonte = NULL;
         }

        GerenciadorGrafico::~GerenciadorGrafico(){
               apagarTodasTexturas();
               delete (window);
        }

        GerenciadorGrafico* GerenciadorGrafico::getGerenciadorGrafico(){
            /*
            *@ return GerenciadorGrafico*
            *
            * Padrao de projeto singleton: garante que eu tenha apenas uma instancia do meu projeto como um todo,
            * isto é, apenas uma janela, apenas um gerenciador de grafico, apenas um gerenciador de eventos, etc.
            */
            if(pGrafico == nullptr){
                pGrafico = new GerenciadorGrafico();
            }
            return pGrafico;
        }

        sf::RenderWindow* GerenciadorGrafico::getWindow(){
            return window;
        }

        void GerenciadorGrafico::clear(){
            window->clear();
        }

        void GerenciadorGrafico::desenhaElemento(sf::RectangleShape* corpo){
            window->draw(*corpo);
        }

        void GerenciadorGrafico::desenhaElemento(sf::Text* texto) {
           window->draw(*texto);
        }

        void GerenciadorGrafico::display(){
            window->display();
        }


        void GerenciadorGrafico::fecharJanela(){
            window->close();
        }

        /* Retorna a textura usada pela entidade */
        sf::Texture* GerenciadorGrafico::carregarTextura(const char* caminho) {
        /* ve se já tem uma ligada */
        std::map<const char*, sf::Texture*>::iterator it = mapaTextura.begin();
         while (it != mapaTextura.end()) {
        if (!strcmp(it->first, caminho))
            return it->second;
        it++;
         }

          /* Se não achou, carregar uma */
        sf::Texture* tex = new sf::Texture();

        if (!tex->loadFromFile(caminho)) {
        cout << "ERROR loading file " << caminho << endl;
        exit(1);
        }

        mapaTextura.insert(std::pair<const char*, sf::Texture*>(caminho, tex));

        return tex;
        }

        const bool GerenciadorGrafico::verificaJanelaAberta(){
            return window->isOpen();
        }

        void GerenciadorGrafico::redefinirTamanhoJanela() {
        float aspectRatio = float(window->getSize().x / float(window->getSize().y));
        view.setSize(sf::Vector2f(HEIGHT * aspectRatio, HEIGHT));
        window->setView(view);
        }

        sf::Vector2u GerenciadorGrafico::getWindowSize() const {
        return window->getSize();
        }

        void GerenciadorGrafico::centerView(sf::Vector2f pos) {
        view.setCenter(pos);
        window->setView(view);
         }

         /* Retorna fonte usada. */
         sf::Font* GerenciadorGrafico::getFont() {
         if (!fonte) {
         fonte = new sf::Font();
         if (!fonte->loadFromFile(FONT_PATH)) {
            cout << "Error loading Font!" << endl;
            exit(1);
          }
         }
         return fonte;
        }

        /* Apagar todas texturas */
        void GerenciadorGrafico::apagarTodasTexturas() {
        std::map<const char*, sf::Texture*>::iterator it;
        for (it = mapaTextura.begin(); it != mapaTextura.end(); ++it)
        delete (it->second);
}




