#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

using namespace std;
// class Utilisateur  (user)
class User {
private:
    static int idU;
    int userID;
    string nom, prenom;
    string username;
    string password;
    string departement;
public:
/* Constructors */
    User(){ userID = idU++; }
    User(string n, string pre, string u, string p, string d):userID(idU++), nom(n), prenom(pre), username(u), password(p), departement(d){}
    // getters
    int getId()const { return userID; }
    string getNom()const { return nom;}
    string getPrenom()const{return prenom ;}
    string getUsername()const { return username;}
    string getDepartement()const {return  departement ;}
    // setters 
    void setNom(string nom) { this->nom = nom;}
    void setPrenom(string prenom) {this->prenom = prenom;}
    void setUsername(string username) {this->username = username;}
    void setPassword(string password) {this->password = password;}
    void setDepartement(string departement) {this->departement = departement;}



    bool authenticate(string u, string p) const {
        return username == u && password == p;
    }
    friend ostream& operator<<(ostream& on, const User& u) {
        on << "-------------------------------" << endl;
        on << "ID de l'utilisateur: " << u.userID << endl;
        on << "Nom: " << u.nom << endl;
        on << "Prenom: " << u.prenom << endl;
        on << "Username: " << u.username << endl;
        on << "Departement: " << u.departement << endl;
        return on;
    }
    friend istream& operator>>(istream& in, User& u){
        cout << "entrer le  nom de l'utilisateur"<< endl;
        in >> u.nom;
        cout << "entrer le prenom de l'utilisateur"<<endl;
        in >> u.prenom;
        cout << "entrer le Username de l'utilisateur"<<endl;
        in >> u.username;
        cout << "entrer le password de  l'utilisateur"<<endl;
        in >> u.password;
        cout << "entrer la departement de  l'utilisateur"<<endl;
        in >> u.departement;
        return in;
    }
    void aff(){ cout<<"\n\t[ID= "<<userID<<"]["<<nom<<":"<<prenom<<"]"; }
    ~User() {}
};
int User::idU = 1;

// class matariel
class Material {
private:
    static  int idM;
    int mId;
    string nom,typeMat,reference,emplacement;
    bool statue;
    vector<User> usersAcce;
public:
    Material(string n, string t, string r, string e,bool s): mId(idM++), nom(n), typeMat(t), reference(r), emplacement(e),statue(s){}
    // getters est setters
    int getId() const {return mId;}
    const string& getNom() const {return nom;}
    void setNom(const string& name) {nom = name;}
    const string& getType() const {return typeMat;}
    void setType(const string& type) {typeMat = type;}
    const string& getReference() const {return reference;}
    void setReference(const string& ref) {reference = ref;}
    const string& getEmplacement() const {return emplacement;}
    void setEmplacement(const string& place) {emplacement = place;}
    bool isStatue() const {return statue;}
    void setStatue(bool status) {statue = status;}

    void usersAcceAff(){
        if(!usersAcce.empty()){
            for (auto u:usersAcce) {
                u.aff();
            }
        } else{ cout<<"*Aucun utilisateur*";}
    }
    friend ostream& operator<<(ostream& on, const Material& m) {
        on <<"\n\n---------------------------\n";
        on << "ID de matariel: " << m.mId << endl;
        on << "Nom: " << m.nom << endl;
        on << "type: " << m.typeMat << endl;
        on << "reference: " << m.reference << endl;
        on << "emplacement: " << m.emplacement << endl;
        on << "statut: ";m.statue?cout<<" en service "<<endl:cout<<" Hors service "<<endl;
        return on;
    }
    friend istream& operator>>(istream& in, Material& m) {
        cout <<"\n---------------------------\n";
        cout << "Entrer le nom du materiel : ";
        in >> m.nom;
        cout << "Entrer le type du materiel : ";
        in >> m.typeMat;
        cout << "Entrer la reference du materiel : ";
        in >> m.reference;
        cout << "Entrer l'emplacement du materiel : ";
        in >> m.emplacement;
        cout << "Le materiel est-il en service ? (1 pour oui, 0 pour non) : ";
        in >> m.statue;
        return in;
    }
    void aff(){
        cout<<"\n\t\t[-"<<mId<<"-]-_-( "<<nom<<" )-_-( "<<typeMat<<" )";
    }
    void affX(){
        cout<<"\n\t__________Matarial__________";
        cout << "ID de matariel: " << mId << endl;
        cout << "Nom: " << nom << endl;
        cout << "type: " << typeMat << endl;
        cout << "reference: " << reference << endl;
        cout << "emplacement: " << emplacement << endl;
        cout << "statut: ";statue?cout<<" en service "<<endl:cout<<" Hors service "<<endl;
    }
    void adduser(User u){
        usersAcce.push_back(u);
    }
    void findU(string username){
        for (auto& u:usersAcce) {
            if (u.getUsername()==username){
                affX();
                cout<<u<<"\n";
            }
        }
    }
    void findUC(string username,string nve){
        for (auto& u:usersAcce) {
            if (u.getUsername()==username){
                setEmplacement(nve);
            }
        }
    }
    void findUB(string username){
        for (auto& u:usersAcce) {
            if (u.getUsername()==username){
                this->isStatue()? setStatue(0): setStatue(1);
            }
        }
    }
    ~Material(){};
};
int Material::idM= 1;

// class provider pour simplify utilisation de users and matarials vectors  
class Provider{
protected:
    static vector<User> users;
    static vector<Material> materials;
    static int quantite;
public:
    Provider(){};
};
vector<User> Provider::users;
vector<Material> Provider::materials;
int Provider::quantite = 0;

// class Admin 
class Admin : public Provider {
private:
    string username;
    string password;
public:
    Admin()=default;
    Admin(string username, string password) : username(username), password(password) {
    }
    bool authenticate(string u, string p) const {
        return username == u && password == p;
    }
    void ajouterMatariel(string n, string t, string r, string e,bool s){
        materials.push_back(Material(n, t, r, e,s));
        quantite=materials.size();
    }
    void modifyMat(int id,string n, string t, string r, string e,bool s) {
        for (auto& m : materials) {
            if (m.getId() == id) {
                m.setNom(n);
                m.setType(t);
                m.setReference(r);
                m.setEmplacement(e);
                m.setStatue(s);
                return;
            }
        }
        throw std::runtime_error("User not found");
    }
};

//class Authentification connection tester aver admin:admin or user:user
class Authentication : public Provider {
private:
    static vector<Admin> admins;
public:
    Authentication() {
        // Add sample admin (temporary for demonstration)
        admins.push_back(Admin("admin", "admin"));
        users.push_back(User("user", "user", "user", "user", "user"));
    }
    bool authenticateAdmin(const string& username, const string& password) const {
        for (const auto& admin : admins) {
            if (admin.authenticate(username, password)) {
                return true;
            }
        }
        return false;
    }
    string nom, prenom,username,password,departement;
    void ajouterUser() {
        cout << "entrer le  nom de l'utilisateur"<< endl;
        cin >> nom;
        cout << "entrer le prenom de l'utilisateur"<<endl;
        cin >> prenom;
        cout << "entrer le Username de l'utilisateur"<<endl;
        cin >> username;
        cout << "entrer le password de  l'utilisateur"<<endl;
        cin >> password;
        cout << "entrer la departement de  l'utilisateur"<<endl;
        cin >> departement;
        users.push_back(User(nom,prenom,username,password,departement));
    }
    int ids;
    void supprimer(){
        cout<<"\n\t La liste des utilisateurs : ";
        for(auto& u:users){
            u.aff();
        }
        cout<<"\n\tentrer le id de utilisateur pour supprimer : ";
        cin>>ids;
        if (!users.empty()){
            auto it = users.begin();
            while (it != users.end()) {
                if (it->getId() == ids) {
                    it = users.erase(it);
                    cout << "\n\tUtilisateur avec l'ID " << ids << " a ete supprimee ." << endl;
                    break;
                } else {
                    ++it;
                }
                if (it == users.end()) {
                    cout << "\n\tUtilisateur avec l'ID " << ids << " non trouve dans le systeme.." << endl;
                }
            }
        }
        else {cout<<"\n\tAucun utilisateur a ce systeme \n";}
    }
    void listUsers(){
        if(!users.empty()){
            for(auto &u:users){
                cout<<u;
            }
        }
        else { cout<<"*Aucun utilisateur*";}
    }
    void modifyUser(int id, string newNom, string newPrenom, string newUsername, string newPassword, string newDepartement) {
        for (auto& user : users) {
            if (user.getId() == id) {
                user.setNom(newNom);
                user.setPrenom(newPrenom);
                user.setUsername(newUsername);
                user.setPassword(newPassword);
                user.setDepartement(newDepartement);
                return;
            }
        }
        throw std::runtime_error("User not found");
    }
    bool authenticateUser(const string& username, const string& password) const {
        if (!users.empty()) {
            for (const auto &user: users) {
                if (user.authenticate(username, password)) {
                    return true;
                }
            }
            return false;
        } else { cout << "Aucune utilisateur!!. Connecte tant qu'admin est cree un !  "; }
    }
    User recherche(int idr){
        for (auto& u:users){
            if(u.getId()==idr){return u;}
        }
        return User("null","null","null","null","null");
        throw runtime_error("User not found");
    }
    User recherche(string idrs){
        for (auto& u:users){
            if(( u.getNom()==idrs) || (u.getPrenom()==idrs)||( u.getUsername()==idrs)||( u.getDepartement()==idrs)  ){return u;}
        }
        return User("null","null","null","null","null");
    }
    string nvnom, nvprenom,nvusername,nvpassword,nvdepartement;
    int id;
    void modifierUser(User u) {
        id=u.getId();
        cout << "entrer le nouveau nom de l'utilisateur"<< endl;
        cin >> nvnom;
        cout << "entrer le nouveau prenom de l'utilisateur"<<endl;
        cin >> nvprenom;
        cout << "entrer le nouveau Username de l'utilisateur"<<endl;
        cin >> nvusername;
        cout << "entrer le nouveau password de  l'utilisateur"<<endl;
        cin >> nvpassword;
        cout << "entrer la nouveau departement de  l'utilisateur"<<endl;
        cin >> nvdepartement;
        modifyUser(id,nvnom,nvprenom, nvusername,nvpassword,nvdepartement);
    }
    Admin a;
    string nomM,typeMat,reference,emplacement;
    bool statue;
    void ajouterM(){
        cout <<"\n---------------------------\n";
        cout << "Entrer le nom du materiel : ";
        cin >> nomM;
        cout << "Entrer le type du materiel : ";
        cin >> typeMat;
        cout << "Entrer la reference du materiel : ";
        cin >> reference;
        cout << "Entrer l'emplacement du materiel : ";
        cin >> emplacement;
        cout << "Le materiel est-il en service ? (1 pour oui, 0 pour non) : ";
        cin >> statue;
        a.ajouterMatariel(nomM,typeMat,reference,emplacement,statue);
    }
    void affM(){
        for (auto& m:materials) {
            m.getType();
            cout<<m;
        }
        cout<<"\n\tQuantite (Stock) "<<quantite;
    }
    int idsm;
    void supprimerM(){
        cout<<"\n\t La list du Matarial : ";
        for(auto& u:materials){
            u.aff();
        }
        cout<<"\n\tetrer l'identifiant de materiel pour supprimer : ";
        cin>>idsm;
        if (!materials.empty()){
            auto it = materials.begin();
            while (it != materials.end()) {
                if (it->getId() == idsm) {
                    it = materials.erase(it);
                    cout << "\n\tmaterial avec l'ID " << idsm << " a ete supprimee ." << endl;
                    quantite=materials.size();
                    break;
                } else {
                    ++it;
                }
                if (it == materials.end()) {
                    cout << "\n\tMaterial avec l'ID " << idsm << " non trouve dans le systeme.." << endl;
                }
            }
        }
        else {cout<<"\n\tmateriel introuvable!! \n";}
    }
    Material rechercheM(int idr){
        for (auto& u:materials){
            if(u.getId()==idr){return u;}
        }
        return Material("null", "null", "null", "null",0);
        throw runtime_error(" materiel introuvable!!!");
    }
    Material rechercheM(string idrs){
        for (auto& u:materials){
            if(( u.getNom()==idrs) || (u.getType()==idrs)||( u.getReference()==idrs)||( u.getEmplacement()==idrs)  ){return u;}
        }
        return Material("null", "null", "null", "null",0);
    }
    Material rechercheM(bool idrb){
        for (auto& u:materials){
            if(( u.isStatue()==idrb)  ){return u;}
        }
        return Material("null", "null", "null", "null",0);
    }
    string nnomM,ntypeMat,nreference,nemplacement;
    bool nstatue;
    int id2;
    void modifiermat(Material u) {
        id2=u.getId();
        cout <<"\n---------------------------\n";
        cout << "Entrer le nouvel nom du materiel : ";
        cin >> nnomM;
        cout << "Entrer le nouvel type du materiel : ";
        cin >> ntypeMat;
        cout << "Entrer la nouvel reference du materiel : ";
        cin >> nreference;
        cout << "Entrer le nouvel emplacement du materiel :";
        cin >> nemplacement;
        cout << "Le materiel est-il en service ? (1 pour oui, 0 pour non) : ";
        cin >> nstatue;
        a.modifyMat(id2,nnomM,ntypeMat,nreference,nemplacement,nstatue);
    }
    void affectationM(User u,int id){
        for(auto& m:materials){
            if(m.getId()==id){
                m.adduser(u);
            }
        }
    }
    int id3;
    void affectation(){
        if (!materials.empty()){
            cout<<"\n\t La liste Matarial : ";
            for(auto& u:materials){
                u.aff();
            }
            cout<<"\n\tentrez l'identifiant de materiel pour attribuer un acces a un utilisateur : ";
            cin>>idsm;
            for(auto& u:materials){
                if (u.getId() == idsm) {
                    id3=u.getId();
                }
            }
            cout<<"\n\t La liste des utilisateurs : ";
            for(auto& u:users){
                u.aff();
            }
            cout<<"\n\tsaisissez l'ID utilisateur à attribuer : ";
            cin>>ids;
            if (!users.empty()){
                for (auto& u:users){
                    if (u.getId() == ids) {
                        affectationM(u,id3);
                    }
                }
            }
            else {cout<<"\n\tAucun utilisateur a ce systeme \n";}
        }
        else {cout<<"\n\tAucun materiel a ce systeme \n";}
    }
    void affichageX(){
        if (!materials.empty()){
            for(auto& m:materials){
                cout<<m;
                m.usersAcceAff();
            }
        } else {cout <<"\n\tAucun materiel";}
    }
    void affichageXX(string user){
        if (!materials.empty()){
            for(auto& m:materials){
                m.findU(user);
            }
        } else {cout <<"\n\tAucun materiel";}
    }
    void changeE(string user,string nvp){
        if (!materials.empty()){
            for(auto& m:materials){
                m.findUC(user,nvp);
            }
        } else {cout <<"\n\tAucun materiel";}
    }
    void changeE(string user){
        if (!materials.empty()){
            for(auto& m:materials){
                m.findUB(user);
            }
        } else {cout <<"\n\tAucun materiel";}
    }
};
vector<Admin> Authentication::admins;

// main 
int main() {
    Authentication auth;
    User u;

    int choix,choix1,typeR,idr,idm,typeM,stope;
    string idrs,nvp,idms,username, password;
    bool authenticated = false;

    do {
        cout << "\n\n\n\tBienvenue ! Veuillez vous connecter [crtl+c pour arreter le systeme]: " << endl;
        cout << "\tNom d'utilisateur : ";
        cin >> username;
        cout << "\tMot de passe : ";
        cin >> password;

        if (auth.authenticateAdmin(username, password)) {
            cout << "\t*********Authentification reussie en tant qu'administrateur." << endl;
            authenticated = true;
            do {
                cout<<"\t***************Admin menu*********** ";
                cout<<"\n\t[1]-Section utilisateur"<<endl;
                cout<<"\n\t[2]-Section matarial"<<endl;
                cout<<"\n\t[0]-Deconnection\n"<<endl;
                cin >> choix1;
                switch (choix1) {
                    case 1:
                        do {
                            cout << "\n\t---------Admin Gestion Utilisateurs---------\n";
                            cout << "\n\t [1]-ajouter utilisateur ";
                            cout << "\n\t [2]-supprimer un utilisateur ";
                            cout << "\n\t [3]-afficher les utilisateurs ";
                            cout << "\n\t [4]-modifier un utilisateur  ";
                            cout << "\n\t [5]-rechercher un utilisateur  ";
                            cout << "\n\t [0]-retour ";
                            cin >> choix;
                            switch (choix){
                                case 1:
                                    cout <<"\n\tajouter un utilisateur\n";
                                    auth.ajouterUser();
                                    break;
                                case 2:
                                    cout <<"\n\tsupprimer un utilisateur\n";
                                    auth.supprimer();
                                    break;
                                case 3:
                                    cout<<"\n\tAfficher les Utilisateurs \n";
                                    auth.listUsers();
                                    break;
                                case 4:
                                    cout<<"\n\tModifier le profil \n";
                                    do {
                                        cout <<" \n\trechercher par ? pour modifier Utilisateur  :  \n";
                                        cout << "\n\t [1]-ID ";
                                        cout << "\n\t [2]-(nom/prenom/username/departement) ";
                                        cin >> typeM;
                                        switch (typeM) {
                                            case 1:
                                                cout<<"\n\tentrer le id de utilisateur pour modifier : ";
                                                cin>>idm;
                                                if(auth.recherche(idm).getNom() =="null"){
                                                    cout<<"\t*****non trouver!!";
                                                }else{auth.modifierUser(auth.recherche(idm));}


                                                break;
                                            case 2:
                                                cout<<"\n\tentrer le (nom/prenom/username/departement) de utilisateur pour modifier : ";
                                                cin>>idms;
                                                if(auth.recherche(idms).getNom() =="null"){
                                                    cout<<"non trouver";
                                                }else{auth.modifierUser(auth.recherche(idms));}
                                                break;
                                        }
                                    }while(typeM!=1 && typeM !=2 );
                                    break;
                                case 5:
                                    do {
                                        cout <<"Recherche Utilisateur par :  \n";
                                        cout << "\n\t [1]-ID ";
                                        cout << "\n\t [2]-(nom/prenom/username/departement) ";
                                        cin >> typeR;
                                        switch (typeR) {
                                            case 1:
                                                cout<<"\n\tentrer le id de utilisateur pour rechercher : ";
                                                cin>>idr;
                                                if(auth.recherche(idr).getNom() =="null"){
                                                    cout<<"non trouver";
                                                }
                                                else {
                                                    cout<<auth.recherche(idr);
                                                }
                                                break;
                                            case 2:
                                                cout<<"\n\tentrer le (nom/prenom/username/departement) de utilisateur pour supprimer : ";
                                                cin>>idrs;
                                                if(auth.recherche(idrs).getNom() =="null"){
                                                    cout<<"non trouver";
                                                }
                                                else {
                                                    cout<<auth.recherche(idrs);
                                                }
                                                break;
                                        }
                                    }while(typeR!=1 && typeR !=2 );
                                    break;
                                case 0:
                                    cout<<"\n\n Routeur... \n\n";
                                    authenticated = false;
                                    choix =0;
                                    break;
                                default :
                                    cout<<"\nChoix invalide.\n";
                                    break;

                            }
                        }while(choix!=0);
                        break;
                    case 2:
                        do {
                            cout << "\n\t---------Admin Gestion Matariels---------\n";
                            cout << "\n\t [1]-ajouter matariel ";
                            cout << "\n\t [2]-supprimer un matariel (actualisation stock auto!)";
                            cout << "\n\t [3]-afficher les matariels ";
                            cout << "\n\t [4]-modifier un matariel  ";
                            cout << "\n\t [5]-rechercher un matariel  ";
                            cout << "\n\t [6]-affecte un utilisateur a un matariel  ";
                            cout << "\n\t [7]-afficher les matarieux est leur user   ";
                            cout << "\n\t [0]-retour ";
                            cin >> choix;
                            switch (choix){
                                case 1:
                                    auth.ajouterM();
                                    break;
                                case 2:
                                    cout <<"\n\t****Suppression un materiel\n";
                                    auth.supprimerM();
                                    break;
                                case 3:
                                    auth.affM();
                                    break;
                                case 4:
                                    do {
                                        cout <<" recherche par ? modifier le materiel  :  \n";
                                        cout << "\n\t [1]-ID ( Recommande! ) ";
                                        cout << "\n\t [2]-(nom/prenom/username/departement) ";
                                        cin >> typeM;
                                        switch (typeM) {
                                            case 1:
                                                cout<<"\n\tentrer le id de matariel pour modifier : ";
                                                cin>>idm;
                                                if(auth.rechercheM(idm).getNom() =="null"){
                                                    cout<<"non trouver";
                                                }else{auth.modifiermat(auth.rechercheM(idm));}

                                                break;
                                            case 2:
                                                cout<<"\n\tentrer le (nom/prenom/username/departement) de matariel pour modifier : ";
                                                cin>>idms;
                                                if(auth.rechercheM(idms).getNom() =="null"){
                                                    cout<<"non trouver";
                                                }else{auth.modifiermat(auth.rechercheM(idms));}
                                                break;
                                        }
                                    }while(typeM!=1 && typeM !=2 );
                                    break;
                                case 5:
                                    do {
                                        cout <<"Recherche Matariel par :  \n";
                                        cout << "\n\t [1]-ID ";
                                        cout << "\n\t [2]-(nom/prenom/username/departement) ";
                                        cout << "\n\t [3]-statue ";
                                        cin >> typeR;
                                        switch (typeR) {
                                            case 3:
                                                bool idrmb;
                                                cout<<"\n\tentrer le statue de matariel pour rechercher : ";
                                                cin>>idrmb;
                                                if(auth.rechercheM(idrmb).getNom() =="null"){
                                                    cout<<"non trouver";
                                                }
                                                else {
                                                    cout<<auth.rechercheM(idrmb);
                                                }
                                                break;
                                            case 1:
                                                int idrm;
                                                cout<<"\n\tentrer le id de utilisateur pour rechercher : ";
                                                cin>>idrm;
                                                if(auth.rechercheM(idrm).getNom() =="null"){
                                                    cout<<"non trouver";
                                                }
                                                else {
                                                    cout<<auth.rechercheM(idrm);
                                                }
                                                break;
                                            case 2:
                                                string idrsm;
                                                cout<<"\n\tentrer le (nom/prenom/username/departement) de utilisateur pour supprimer : ";
                                                cin>>idrsm;
                                                if(auth.rechercheM(idrsm).getNom() =="null"){
                                                    cout<<"non trouver";
                                                }
                                                else {
                                                    cout<<auth.rechercheM(idrsm);
                                                }
                                                break;
                                        }
                                    }while(typeR!=1 && typeR !=2 && typeR !=3 );
                                    break;
                                case 6:
                                    cout<<"\n affectation ......";
                                    auth.affectation();
                                    break;
                                case 7:
                                    auth.affichageX();
                                    break;
                                case 0:
                                    cout<<"\n\n Routeur... \n\n";
                                    authenticated = false;
                                    choix =0;
                                    break;
                                default :
                                    cout<<"\nChoix invalide.\n";
                                    break;

                            }
                        }while(choix!=0);
                        break;
                    case 0:
                        cout<<"\nDeconnection....\n";
                        authenticated = false;
                        choix =0;
                        break;
                }

            } while (choix1!=0);
        } else if (auth.authenticateUser(username, password)) {
            cout << "Authentification reussie en tant que  utilisateur." << endl;
            authenticated = true;
            do {
                cout << "\n\t---------User menu---------\n";
                cout << "\n\t [1]-Afficher leur matariels ";
                cout << "\n\t [2]-chnager emplacement de leur matariels ";
                cout << "\n\t [3]-chnager le statue de leur matariels ";
                cout << "\n\t [0]-deconnection ";
                cin >> choix;
                switch (choix){
                    case 1:
                        auth.affichageXX(username);
                        break;
                    case 2:
                        cout<<"donner le neveau emplacement de matariel\n";
                        cin>>nvp;
                        auth.changeE(username,nvp);
                        break;
                    case 3:
                        cout<<"changement de statue  de matariel\n";

                        auth.changeE(username);
                        break;
                    case 0:
                        cout<<"\n\n Deconnexion... \n\n";
                        authenticated = false;
                        choix =0;
                        break;
                    default :
                        cout<<"Choix invalide.\n";
                        break;

                }
            }while(choix!=0);

        } else {
            cout << "Authentification echouee. Nom d'utilisateur ou mot de passe incorrect." << endl;

        }
    } while (!authenticated);

    return 0;
}

