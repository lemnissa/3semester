#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

struct vector3 {
    double x;
    double y;
    double z;

    double length(vector3 r) {
        double L2 = pow((r.x - x), 2) + pow((r.y - y), 2) + pow((r.z - z), 2);
        return pow(L2, 0.5);
    }

    vector3 r(vector3 r) {
        vector3 r1 =  {x-r.x, y-r.y, z-r.z};
        return r1;
    }

    string vector3_to_s() {
        string s = "{" + to_string(x) + "," + to_string(y) + "," + to_string(z) + "}";
        return s;
    }
};

class Logger {
public:
    Logger() = default;
    void log(const string& s) {
        l.push_back(s);
    }
    ~Logger() = default;
private:
    vector<string> l;
};

class Particle {
protected:
    double mass = 0;
    double charge = 0;
    vector3 coordinate = {0, 0, 0};
    vector3 velocity = {0, 0,0};
    vector3 force = {0, 0, 0};
    string name;
    static Logger logger;
    double dt = 0;
    static int num_particular;
public:
    Particle() {num_particular++;}
    explicit Particle(vector3 r, vector3 v, double mass_, double charge_, string name_, double dt_) :
        mass(mass_), charge(charge_), coordinate(r), velocity(v), name(name_), dt(dt_) {        name = name_;
        logger.log("created: " + name_);
        num_particular++;
    }
    void change_force(Particle* p) {
        double l = coordinate.length(p->coordinate);
        vector3 r = coordinate.r(p->coordinate);
        double f = p->charge*charge/(pow(l, 2));
        force.x = force.x + f*r.x/l;
        force.z = force.z + f*r.z/l;
        force.y = force.y + f*r.y/l;
    }

    void interaction() {
        velocity = {velocity.x + force.x/mass*dt, velocity.y + force.y/mass*dt, velocity.z + force.z/mass*dt};
        force = {0, 0, 0};
        coordinate = {coordinate.x + velocity.x*dt, coordinate.y + velocity.y*dt, coordinate.z + velocity.z*dt};
        logger.log("change: name=" + name + ", coordinate=" + coordinate.vector3_to_s());
    }

    string getNum() const {
        return to_string(num_particular);
    }

    string getName() const {
        return name;
    }

    string getEnergy() {
        return to_string(mass * pow(velocity.length({0, 0, 0}), 2) / 2);
    }

    string getCoor() {
        return coordinate.vector3_to_s();
    }

    string getVel() {
        return velocity.vector3_to_s();
    }

    ~Particle() {
        logger.log("destroyed: " + name);
        num_particular--;
    }
};

int Particle::num_particular = 0;
Logger Particle::logger;

class Electron : public Particle {
public:
    explicit Electron(vector3 coords, vector3 vel, string name_, double dt) : Particle(coords, vel, 0.1, -1, name_, dt) {
        name = "e_" + name_;
    }
    ~Electron();
};

class Proton : public Particle {
public:
    explicit Proton(vector3 coords, vector3 vel, string name_, double dt) : Particle(coords, vel, 1, 1, name_, dt) {
        name = "p_" + name_;
    }
    ~Proton();
};

class Neutron : public Particle {
public:
    explicit Neutron(vector3 coords, vector3 vel, string name_, double dt) : Particle(coords, vel, 1, 0.01, name_, dt) {
        name = "n_" + name_;
    }
    ~Neutron();
};

class World {
    double dt = 0.1;
public:
    vector<Particle *> v;

    double rand_v(int energy) const {
        double pos = 1;
        if (rand()%2 == 0) {
            pos = -1;
        }
        return pos * (rand()% energy) / 100;
    }

    double rand_r() const {
        double pos = 1;
        if (rand()%2 == 0) {
            pos = -1;
        }
        return pos * (rand()%1000) / 100;
    }

    void addParticle(int type, string name) {
        int energy = rand()%1000;
        vector3 vel = {rand_v(energy), rand_v(energy), rand_v(energy)};
        vector3 coor = {rand_r(), rand_r(), rand_r()};
        Particle *p = NULL;
        if (type == 0) {
            p = (Particle *) new Electron(coor, vel, name, dt);
        } else if (type == 1) {
            p = (Particle *) new Proton(coor, vel, name, dt);
        } else if (type == 2) {
            p = (Particle *) new Neutron(coor, vel, name, dt);
        }
        if (p != NULL) v.push_back(p);
    }

    void deleteParticle(const Particle* p) {
        for (auto i = 0; i < v.size(); i++) {
            if (v[i] == p) {
                delete p;
                v.erase(v.begin() + i);

                break;
            }
        }
    }

    void interaction() {
        for (auto &pi : v) {
            for (auto &pj : v) {
                if (pi != pj) {
                    pi->change_force(pj);
                }
            }
        }
        for (auto p:v) {
            p->interaction();
        }
    }

    ~World() {
        for (auto p : v) {
            delete p;
        }
    }
};

int main() {
    int epoch = 0;
    World world;
    world.addParticle(0, "1");
    world.addParticle(1, "2");
    world.addParticle(2, "3");
    world.addParticle(0, "4");
    cout << world;
    for (auto i = 0; i < epoch; i++) {
        world.interaction();
        cout << world;
    }
    world.deleteParticle(world.v[0]);
    cout << world;
    cout << world.v[0]->getNum() << "\n";
}
