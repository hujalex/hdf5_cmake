// #include <iostream>
// #include <string>
// #include <vector>
// #include <fstream>
// #include <highfive/H5File.hpp>
// #include <highfive/H5DataSet.hpp>
// #include <highfive/H5DataSpace.hpp>
// #include <highfive/H5PropertyList.hpp>

// using namespace std;
// using namespace HighFive;

// const std::string FILE_NAME("../double_foo.h5");
// const std::string DATASET_NAME("dset");

// // Check if a file exists
// bool file_exists(const std::string& name) {
//     if (FILE *file = fopen(name.c_str(), "r")) {
//         fclose(file);
//         return true;
//     } else {
//         return false;
//     }
// }

// // Initialize the file
// File initialize_file(bool file_exists) {
//     if (file_exists) {
//         return File(FILE_NAME, File::ReadWrite);
//     }
//     return File(FILE_NAME, File::ReadWrite | File::Create | File::Truncate);
// }

// // Create or retrieve the dataset
// DataSet create_dataset(bool file_exists, DataSpace& dataspace, File& file) {
//     if (file_exists) {
//         return file.getDataSet(DATASET_NAME);
//     }
//     DataSetCreateProps props;
//     props.add(Chunking(std::vector<hsize_t>{2, 2}));
//     return file.createDataSet(DATASET_NAME, dataspace, create_datatype<float>(), props);
// }

// void append(DataSet & dataset, size_t num_rows, size_t num_cols) {

//     const size_t cols = 10; // Needs to be const because dataset.select requires fixed size at runtime

//     dataset.resize({num_rows + 1, cols});
//     double arr[1][cols];
//     for (double * it = &arr[0][0]; it != &arr[0][cols]; ++it) {
//         *it = 3.141592653589793;
//     }
//     dataset.select({num_rows,0}, {1, cols}).write(arr);
// } 

// int main(void) {
//     // Create a dataspace with initial shape and max shape
//     DataSpace dataspace({0,0}, {DataSpace::UNLIMITED, DataSpace::UNLIMITED});

//     bool does_file_exist = file_exists("../double_foo.h5");

//     // Initialize file and dataset
//     File file = initialize_file(does_file_exist);
//     DataSet dataset = create_dataset(does_file_exist, dataspace, file);

//     append(dataset, dataset.getDimensions()[0], dataset.getDimensions()[1]);

//     // // Write into the initial part of the dataset
//     // double t1[3][1] = {{2.0}, {2.0}, {4.0}};
//     // dataset.select({0, 0}, {3, 1}).write(t1);

//     // // Resize the dataset to a larger size
//     // dataset.resize({4, 6});
//     // double t2[1][3] = {{4.0, 8.0}};
//     // dataset.select({3, 3}, {1, 2}).write(t2);

//     // dataset.resize({5, 6});
//     // double t3[1][6];
//     // for (double* it = &t3[0][0]; it != &t3[0][6]; ++it) {
//     //     *it = 3.14152677;
//     // }
//     // dataset.select({4, 0}, {1, 6}).write(t3);

//     // Read back the dataset

//     //! dataset.getDimensions gets the dimensions of the dataset



//     // std::vector<std::vector<double>> result;
//     // dataset.read(result);

//     // // Print the dataset
//     // for (auto row: result) {
//     //     for (auto col: row) {
//     //         std::cout << " " << col;
//     //     }
//     //     std::cout << std::endl;
//     // }

//     return 0;
// }

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <highfive/H5File.hpp>
#include <highfive/H5DataSet.hpp>
#include <highfive/H5DataSpace.hpp>
#include <highfive/H5PropertyList.hpp>

using namespace std;
using namespace HighFive;

const std::string FILE_NAME("../float32_foo.h5");
const std::string DATASET_NAME("dset");

const size_t cols = 100; 


// Check if a file exists
bool file_exists(const std::string& name) {
    if (FILE* file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

// Initialize the file
File initialize_file(bool file_exists) {
    if (file_exists) {
        return File(FILE_NAME, File::ReadWrite);
    }
    return File(FILE_NAME, File::ReadWrite | File::Create | File::Truncate);
}

// Create or retrieve the dataset
DataSet create_dataset(bool file_exists, DataSpace& dataspace, File& file) {
    if (file_exists) {
        return file.getDataSet(DATASET_NAME);
    }
    DataSetCreateProps props;
    props.add(Chunking(std::vector<hsize_t>{100, cols}));
    props.add(Deflate(6));
    return file.createDataSet(DATASET_NAME, dataspace, create_datatype<float>(), props); // Float32 //! DataSet Size deteremined only by chunking
}

// Append rows to the dataset
void append(DataSet& dataset, size_t num_rows, size_t num_cols) {
// Needs to be const because dataset.select requires fixed size at runtime

    dataset.resize({num_rows + 1, cols}); // Resize to accommodate new row
    float arr[1][cols];                   // Float32 array

    for (float* it = &arr[0][0]; it != &arr[0][cols]; ++it) {
        *it = 3.141592653589793f; // Assign float values
    }

    dataset.select({num_rows, 0}, {1, cols}).write(arr); // Write the row to the dataset
}

int main(void) {
    // Create a dataspace with initial shape and max shape
    DataSpace dataspace({0, cols}, {DataSpace::UNLIMITED, cols}); // Up to 1000 rows, fixed 10 columns


    bool does_file_exist = file_exists(FILE_NAME);

    // Initialize file and dataset
    File file = initialize_file(does_file_exist);
    DataSet dataset = create_dataset(does_file_exist, dataspace, file);

    append(dataset, dataset.getDimensions()[0], dataset.getDimensions()[1]);

    return 0;
}

