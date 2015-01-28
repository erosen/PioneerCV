#include <pylon/PylonIncludes.h>
using namespace Pylon;
using namespace std;

int main(int argc, char** argv)
{
	
	Pylon::PylonAutoInitTerm autoInitTerm;  // PylonInitialize() will be called now

	try
	{
		// Create an instant camera object with the first camera device found.
		CInstantCamera camera(CTlFactory::GetInstance().CreateFirstDevice());

		// Print the model name of the camera.
		cout << "Using device " << camera.GetDeviceInfo().GetModelName() << endl;

		// This smart pointer will receive the grab result data.
		CGrabResultPtr ptrGrabResult;

		cout << "Grab using single frame acquisition:" << endl << endl;

		// Register the standard configuration event handler for configuring single frame acquisition.
		// The previous configuration is removed by setting the registration mode to RegistrationMode_ReplaceAll.
		camera.RegisterConfiguration(new CAcquireSingleFrameConfiguration, RegistrationMode_ReplaceAll, Cleanup_Delete);

		// To continuously grab single images it is much more efficient to open the camera before grabbing.
		// Note: The software trigger mode (see above) should be used for grabbing single images if you want to maximize frame rate.

		// Now, the camera parameters are applied in the OnOpened method of the configuration object.
		camera.Open();

		// Additional parameters could be set here.

		// Grab some images for demonstration.
		camera.GrabOne(5000, ptrGrabResult);
		camera.GrabOne(5000, ptrGrabResult);
		camera.GrabOne(5000, ptrGrabResult);

		// Close the camera.
		camera.Close();
	}
	catch (GenICam::GenericException &e)
	{
		// Error handling.
		cerr << "An exception occurred." << endl
			<< e.GetDescription() << endl;
	}

	return 0;

}