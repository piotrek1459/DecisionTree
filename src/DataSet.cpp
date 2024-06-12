#include "DataSet.h"
 auto DataSet::return_storage() {
    auto storage = make_storage("../df.sqlite",
                                make_table("data",
                                           make_column("id", &Data::id, primary_key()),
                                           make_column("age", &Data::age),
                                           make_column("sex", &Data::sex),
                                           make_column("restbp", &Data::restbp),
                                           make_column("chol", &Data::chol),
                                           make_column("fbs", &Data::fbs),
                                           make_column("thalach", &Data::thalach),
                                           make_column("exang", &Data::exang),
                                           make_column("oldpeak", &Data::oldpeak),
                                           make_column("ca", &Data::ca),
                                           make_column("cp1", &Data::cp1),
                                           make_column("cp2", &Data::cp2),
                                           make_column("cp3", &Data::cp3),
                                           make_column("cp4", &Data::cp4),
                                           make_column("restecg1", &Data::restecg1),
                                           make_column("restecg2", &Data::restecg2),
                                           make_column("restecg3", &Data::restecg3),
                                           make_column("slope1", &Data::slope1),
                                           make_column("slope2", &Data::slope2),
                                           make_column("slope3", &Data::slope3),
                                           make_column("thal3", &Data::thal3),
                                           make_column("thal6", &Data::thal6),
                                           make_column("thal7", &Data::thal7),
                                           make_column("hd", &Data::hd)));
    storage.sync_schema();
    return storage;
}

void DataSet::insert_into_storage() {
    auto storage = return_storage();
    storage.remove_all<Data>();
    std::ifstream f("../data/data.csv");
    aria::csv::CsvParser parser(f);
    int count = 0;
    for (auto& row : parser) {
        if (std::find(row.begin(), row.end(), "?") != row.end()) {
            count++;
        } else {
            int age = stoi(row[0]);
            int sex = stoi(row[1]);
            int restbp = stoi(row[3]);
            int chol = stoi(row[4]);
            int fbs = stoi(row[5]);
            int thalach = stoi(row[7]);
            int exang = stoi(row[8]);
            float oldpeak = stof(row[9]);
            int ca = stoi(row[11]);
            int cp1, cp2, cp3, cp4;
            switch (stoi(row[2])) {
                case 1: cp1 = 1; cp2 = cp3 = cp4 = 0; break;
                case 2: cp2 = 1; cp1 = cp3 = cp4 = 0; break;
                case 3: cp3 = 1; cp1 = cp2 = cp4 = 0; break;
                case 4: cp4 = 1; cp1 = cp2 = cp3 = 0; break;
            }
            int restecg1, restecg2, restecg3;
            switch (stoi(row[6])) {
                case 0: restecg1 = 1; restecg2 = restecg3 = 0; break;
                case 1: restecg2 = 1; restecg1 = restecg3 = 0; break;
                case 2: restecg3 = 1; restecg1 = restecg2 = 0; break;
            }
            int slope1, slope2, slope3;
            switch (stoi(row[10])) {
                case 1: slope1 = 1; slope2 = slope3 = 0; break;
                case 2: slope2 = 1; slope1 = slope3 = 0; break;
                case 3: slope3 = 1; slope1 = slope2 = 0; break;
            }
            int thal3, thal6, thal7;
            switch (stoi(row[12])) {
                case 3: thal3 = 1; thal6 = thal7 = 0; break;
                case 6: thal6 = 1; thal3 = thal7 = 0; break;
                case 7: thal7 = 1; thal3 = thal6 = 0; break;
            }
            int hd = (stoi(row[13]) == 0) ? 0 : 1;

            storage.insert(Data{-1, age, sex, restbp, chol, fbs, thalach, exang, oldpeak, ca,
                                cp1, cp2, cp3, cp4, restecg1, restecg2, restecg3, slope1, slope2, slope3,
                                thal3, thal6, thal7, hd});
        }
    }
    std::cout << "There was/were " << count << " incomplete line/s\n";
}

void DataSet::print_storage() {
    auto storage = return_storage();
    for (auto& u: storage.iterate<Data>()) {
        cout << storage.dump(u) << endl;
    }
}

std::vector<DataSet::Data> DataSet::fetch_data() {
    auto storage = return_storage();
    return storage.get_all<Data>();
}

std::vector<std::vector<float>> DataSet::fetch_X_y() {
    auto data = DataSet::fetch_data();
    std::vector<std::vector<float>> dataset;
    for (auto& row : data) {
        dataset.push_back({(float)row.age, (float)row.sex, (float)row.restbp, (float)row.chol, (float)row.fbs, (float)row.thalach, (float)row.exang, row.oldpeak, (float)row.ca,
                           (float)row.cp1, (float)row.cp2, (float)row.cp3, (float)row.cp4, (float)row.restecg1, (float)row.restecg2, (float)row.restecg3, (float)row.slope1, (float)row.slope2, (float)row.slope3,
                           (float)row.thal3, (float)row.thal6, (float)row.thal7, (float)row.hd});
    }
    return dataset;
}