#include <bits/stdc++.h>
#define ll long long

using namespace std;

class Contributer{
public:
    string name;
    unordered_map<string, int> skills; 
    int skill_count;

    Contributer(string _name, int _skill_count){
        name = _name;
        skill_count = _skill_count;
    }

    void addSkill(string skill, int score){
        skills[skill] = score;
    }
};

class Project{
public:
    string name;
    int number_of_days;
    int score;
    int best_before;
    int number_of_roles;

    vector<pair<string, int>> req_skills;

    Project(string _name, int _number_of_days, int _score, int _best_before, int _number_of_roles){
        name = _name;
        number_of_days = _number_of_days;
        score = _score;
        best_before = _best_before;
        number_of_roles = _number_of_roles;
    }

    void addSkill(string _name, int level){
        req_skills.push_back({_name, level});
    }
};

unordered_map<string, vector<Contributer*>> skill_to_cont;

int main(int argc, char const *argv[]) {
	ifstream infile;
	ofstream outfile;

	infile.open(argv[1]);
	outfile.open(argv[2]);

    int c, p;
    infile >> c >> p;

    vector<Contributer> conts; 
    
    for(int i=0; i<c; i++){
        string temp_cont;
        int temp_skill_count;

        infile >> temp_cont >> temp_skill_count;
        Contributer temp_class(temp_cont, temp_skill_count);
        conts.push_back(temp_class);
        for(int k=0; k<temp_skill_count; k++){
            string temp_skill;
            int temp_score;
            infile >> temp_skill >> temp_score;
            conts[i].addSkill(temp_skill, temp_score);
        }
    }

    vector<Project> projects;

    for(int i=0; i<p; i++){
        string _name;
        int _number_of_days, _score, _best_before, _number_of_roles;
        
        infile >> _name >> _number_of_days >> _score >> _best_before >> _number_of_roles;
        Project temp(_name, _number_of_days, _score, _best_before, _number_of_roles);
        projects.push_back(temp);

        for(int k=0; k<_number_of_roles; k++){
            string _skill_name;
            int _req_score;
            infile >> _skill_name >> _req_score;
            projects[i].addSkill(_skill_name, _req_score);
        }
    }

    sort(projects.begin(), projects.end(), [](const Project &a, const Project &b){ 
        return (a.score / (a.best_before * a.number_of_days)) > (b.score / (b.best_before * b.number_of_days));
            });



    for(int i=0; i<conts.size(); i++){
        for(auto temp_skill: conts[i].skills){
            
                if(skill_to_cont.find(temp_skill.first) == skill_to_cont.end()){
                    vector<Contributer*> vec;
                    skill_to_cont[temp_skill.first] = vec;
    
                }
                skill_to_cont[temp_skill.first].push_back(&conts[i]);
    
        }
    }
    


    vector<vector<string>> all_res;

    for(auto temp_project: projects){
        vector<string> res;
        res.push_back(temp_project.name);

        for(auto temp_skill: temp_project.req_skills){
            //mentor olabilir mi?
            bool flag = true;

            if(res.size() > 2){
               for(int i=1; i<res.size(); i++){
                   int index;
                   for(int k=0; k<conts.size(); k++){
                       if(conts[k].name == res[i]){
                           index = k;
                           break;
                       }
                    }
                    //cout << index << endl;
                    if(conts[index].skills.find(temp_skill.first) == conts[index].skills.end()){
                        break;
                    }else if(conts[index].skills[temp_skill.first] >  temp_skill.second){
                        for(int l=0; l<conts.size(); l++){
                            if(find(res.begin(), res.end(), conts[l].name) == res.end()){

                                res.push_back(conts[l].name);
                                flag = false;
                            }                            
                        }

                        
                    }



               }
            }
            

            // Normal atama
            if(flag){
                for(auto temp_cont: skill_to_cont[temp_skill.first]){
                    
                    if(find(res.begin(), res.end(), temp_cont->name) == res.end()){

                        if(temp_cont->skills[temp_skill.first] >= temp_skill.second){

                            res.push_back(temp_cont->name);

                            break;
                        }
                    }
                } 
            }
        }

        if(res.size() == temp_project.req_skills.size()+1){
            all_res.push_back(res);
            for(int i=1; i<res.size(); i++){
                for(auto temp_cont: conts){
                    if(temp_cont.name == res[i]){
                        temp_cont.skills[temp_project.req_skills[i-1].first]++; 
                    }
                }
                
            }
        }
            
    }   

    

    outfile << all_res.size() << endl;
    for(auto temp: all_res){
        outfile << temp[0] << endl;
        for(int i=1; i<temp.size(); i++){
            outfile << temp[i] << " ";
        }
        outfile << '\n';
    }

    cout << "Finish" << endl;

}


