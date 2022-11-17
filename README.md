# Solar System Simulation with Epochal Time Model
This project is a 3D OpenGL C++ Solar System Simulator, originally created by [Ryan Pridgeon](https://github.com/RyanPridgeon/solarsystem). I took that simulation and implimented the Epochal Time Model, as described by Rich Hickey in his talk [Are We There Yet?](https://github.com/matthiasn/talk-transcripts/blob/9f33e07ac392106bccc6206d5d69efe3380c306a/Hickey_Rich/AreWeThereYet.md#user-content-slide-31)

## About the Epochal Time Model

The following image is from the same Are We There Yet? talk mentioned above.

![Epochal Time Model] (https://donnywinston.com/img/hickey_are-we-there-yet_epochal-time-model.jpg)

The idea of the epochal time model is to capture the passage of time as an attribute in software. Instead of modifying objects (and permentantly losing the original information) any time we would modify an object we instead clone it with the updated value and append it to an ever growing array that represents the object. With this model, we can access the object at any point in its history. We never lose any data.

## The Intent of the Project

My main intent for developing this project was to see if the sheer amount of data the Epochal Time Model generates is feasable for a simulation on a relatively weak local machine. Instead of maintaining the display data for a handful of planets, we're storing the thousands of planets - and that number continues to grow as the simulation continues to run.

While the slow down was noticeable after ten minutes of the simulation running, a home laptop was able to adequetly prototype and run the resulting program without needing to involve more powerful cloud computing.
