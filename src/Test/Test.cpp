/*
* Tests for Simd Library (http://simd.sourceforge.net).
*
* Copyright (c) 2011-2016 Yermalayeu Ihar,
*               2014-2015 Antonenka Mikhail.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/
#include "Test/TestPerformance.h"
#include "Test/TestLog.h"

namespace Test
{
    typedef bool (*AutoTestPtr)(); 
    typedef bool (*DataTestPtr)(bool create);
	typedef bool (*SpecialTestPtr)();

    struct Group
    {
        String name;
        AutoTestPtr autoTest;
		DataTestPtr dataTest;
		SpecialTestPtr specialTest;
        Group(const String & n, const AutoTestPtr & a, const DataTestPtr & d, const SpecialTestPtr & s)
            : name(n)
            , autoTest(a)
            , dataTest(d)
			, specialTest(s)
        {
        }
    };
    typedef std::vector<Group> Groups;
    Groups g_groups;

#define TEST_ADD_GROUP(name) \
    bool name##AutoTest(); \
    bool name##DataTest(bool create); \
    bool name##AddToList(){ g_groups.push_back(Group(#name, name##AutoTest, name##DataTest, NULL)); return true; } \
    bool name##AtList = name##AddToList();

#define TEST_ADD_GROUP_EX(name) \
    bool name##AutoTest(); \
    bool name##DataTest(bool create); \
    bool name##SpecialTest(); \
    bool name##AddToList(){ g_groups.push_back(Group(#name, name##AutoTest, name##DataTest, name##SpecialTest)); return true; } \
    bool name##AtList = name##AddToList();

#define TEST_ADD_GROUP_ONLY_SPECIAL(name) \
    bool name##SpecialTest(); \
    bool name##AddToList(){ g_groups.push_back(Group(#name, NULL, NULL, name##SpecialTest)); return true; } \
    bool name##AtList = name##AddToList();

    TEST_ADD_GROUP(AbsDifferenceSum);
    TEST_ADD_GROUP(AbsDifferenceSumMasked);
    TEST_ADD_GROUP(AbsDifferenceSums3x3);
    TEST_ADD_GROUP(AbsDifferenceSums3x3Masked);
    TEST_ADD_GROUP(SquaredDifferenceSum);
    TEST_ADD_GROUP(SquaredDifferenceSumMasked);
    TEST_ADD_GROUP(SquaredDifferenceSum32f);
    TEST_ADD_GROUP(SquaredDifferenceKahanSum32f);

    TEST_ADD_GROUP(AddFeatureDifference);

	TEST_ADD_GROUP(AnnConvert);
	TEST_ADD_GROUP(AnnProductSum);
	TEST_ADD_GROUP(AnnRoughSigmoid);
	TEST_ADD_GROUP(AnnSigmoid);
    TEST_ADD_GROUP(AnnUpdateWeights);

    TEST_ADD_GROUP(BgraToBgr);
    TEST_ADD_GROUP(BgraToGray);
    TEST_ADD_GROUP(BgrToGray);
    TEST_ADD_GROUP(BgrToHsl);
    TEST_ADD_GROUP(BgrToHsv);
    TEST_ADD_GROUP(GrayToBgr);

    TEST_ADD_GROUP(BgraToBayer);
    TEST_ADD_GROUP(BgrToBayer);

    TEST_ADD_GROUP(BgrToBgra);
    TEST_ADD_GROUP(GrayToBgra);

    TEST_ADD_GROUP(BgraToYuv420p);
    TEST_ADD_GROUP(BgraToYuv422p);
    TEST_ADD_GROUP(BgraToYuv444p);
    TEST_ADD_GROUP(BgrToYuv420p);
    TEST_ADD_GROUP(BgrToYuv422p);
    TEST_ADD_GROUP(BgrToYuv444p);

    TEST_ADD_GROUP(BackgroundGrowRangeSlow);
    TEST_ADD_GROUP(BackgroundGrowRangeFast);
    TEST_ADD_GROUP(BackgroundIncrementCount);
    TEST_ADD_GROUP(BackgroundAdjustRange);
    TEST_ADD_GROUP(BackgroundAdjustRangeMasked);
    TEST_ADD_GROUP(BackgroundShiftRange);
    TEST_ADD_GROUP(BackgroundShiftRangeMasked);
    TEST_ADD_GROUP(BackgroundInitMask);

    TEST_ADD_GROUP(BayerToBgr);

    TEST_ADD_GROUP(BayerToBgra);

    TEST_ADD_GROUP(Bgr48pToBgra32);

    TEST_ADD_GROUP(Binarization);
    TEST_ADD_GROUP(AveragingBinarization);

    TEST_ADD_GROUP(ConditionalCount8u);
    TEST_ADD_GROUP(ConditionalCount16i);
    TEST_ADD_GROUP(ConditionalSum);
    TEST_ADD_GROUP(ConditionalSquareSum);
    TEST_ADD_GROUP(ConditionalSquareGradientSum);
	TEST_ADD_GROUP(ConditionalFill);

    TEST_ADD_GROUP(ContourMetricsMasked);
    TEST_ADD_GROUP(ContourAnchors);

    TEST_ADD_GROUP(Copy);
    TEST_ADD_GROUP(CopyFrame);

    TEST_ADD_GROUP(Crc32c);

    TEST_ADD_GROUP(DeinterleaveUv);

    TEST_ADD_GROUP(DetectionHaarDetect32fp);
    TEST_ADD_GROUP(DetectionHaarDetect32fi);
    TEST_ADD_GROUP(DetectionLbpDetect32fp);
    TEST_ADD_GROUP(DetectionLbpDetect32fi);
    TEST_ADD_GROUP(DetectionLbpDetect16ip);
    TEST_ADD_GROUP(DetectionLbpDetect16ii);
    TEST_ADD_GROUP_ONLY_SPECIAL(Detection);

    TEST_ADD_GROUP(AlphaBlending);

    TEST_ADD_GROUP(EdgeBackgroundGrowRangeSlow);
    TEST_ADD_GROUP(EdgeBackgroundGrowRangeFast);
    TEST_ADD_GROUP(EdgeBackgroundIncrementCount);
    TEST_ADD_GROUP(EdgeBackgroundAdjustRange);
    TEST_ADD_GROUP(EdgeBackgroundAdjustRangeMasked);
    TEST_ADD_GROUP(EdgeBackgroundShiftRange);
    TEST_ADD_GROUP(EdgeBackgroundShiftRangeMasked);

    TEST_ADD_GROUP(Fill);
    TEST_ADD_GROUP(FillFrame);
    TEST_ADD_GROUP(FillBgra);
    TEST_ADD_GROUP(FillBgr);

    TEST_ADD_GROUP(Histogram);
    TEST_ADD_GROUP(HistogramMasked);
    TEST_ADD_GROUP(AbsSecondDerivativeHistogram);

    TEST_ADD_GROUP(HogDirectionHistograms);

    TEST_ADD_GROUP(Integral);

    TEST_ADD_GROUP(InterferenceIncrement);
    TEST_ADD_GROUP(InterferenceIncrementMasked);
    TEST_ADD_GROUP(InterferenceDecrement);
    TEST_ADD_GROUP(InterferenceDecrementMasked);

	TEST_ADD_GROUP(InterleaveUv);

	TEST_ADD_GROUP(MeanFilter3x3);
	TEST_ADD_GROUP(MedianFilterRhomb3x3);
    TEST_ADD_GROUP(MedianFilterRhomb5x5);
    TEST_ADD_GROUP(MedianFilterSquare3x3);
    TEST_ADD_GROUP(MedianFilterSquare5x5);
    TEST_ADD_GROUP(GaussianBlur3x3);
    TEST_ADD_GROUP(AbsGradientSaturatedSum);
    TEST_ADD_GROUP(LbpEstimate);
    TEST_ADD_GROUP(NormalizeHistogram);
    TEST_ADD_GROUP(SobelDx);
    TEST_ADD_GROUP(SobelDxAbs);
    TEST_ADD_GROUP(SobelDy);
    TEST_ADD_GROUP(SobelDyAbs);
    TEST_ADD_GROUP(ContourMetrics);
    TEST_ADD_GROUP(Laplace);
    TEST_ADD_GROUP(LaplaceAbs);

    TEST_ADD_GROUP(OperationBinary8u);
    TEST_ADD_GROUP(OperationBinary16i);
    TEST_ADD_GROUP(VectorProduct);

    TEST_ADD_GROUP(ReduceGray2x2);
    TEST_ADD_GROUP(ReduceGray3x3);
    TEST_ADD_GROUP(ReduceGray4x4);
    TEST_ADD_GROUP(ReduceGray5x5);

    TEST_ADD_GROUP(Reorder16bit);
    TEST_ADD_GROUP(Reorder32bit);
    TEST_ADD_GROUP(Reorder64bit);

    TEST_ADD_GROUP_EX(ResizeBilinear);

    TEST_ADD_GROUP(SegmentationShrinkRegion);
    TEST_ADD_GROUP(SegmentationFillSingleHoles);
    TEST_ADD_GROUP(SegmentationChangeIndex);
    TEST_ADD_GROUP(SegmentationPropagate2x2);

    TEST_ADD_GROUP(ShiftBilinear);

    TEST_ADD_GROUP(GetStatistic);
    TEST_ADD_GROUP(GetMoments);
    TEST_ADD_GROUP(GetRowSums);
    TEST_ADD_GROUP(GetColSums);
    TEST_ADD_GROUP(GetAbsDyRowSums);
    TEST_ADD_GROUP(GetAbsDxColSums);
    TEST_ADD_GROUP(ValueSum);
    TEST_ADD_GROUP(SquareSum);
    TEST_ADD_GROUP(SobelDxAbsSum);
    TEST_ADD_GROUP(SobelDyAbsSum);
    TEST_ADD_GROUP(LaplaceAbsSum);
    TEST_ADD_GROUP(CorrelationSum);

    TEST_ADD_GROUP(StretchGray2x2);

    TEST_ADD_GROUP(SvmSumLinear);

    TEST_ADD_GROUP(TextureBoostedSaturatedGradient);
    TEST_ADD_GROUP(TextureBoostedUv);
    TEST_ADD_GROUP(TextureGetDifferenceSum);
    TEST_ADD_GROUP(TexturePerformCompensation);

    TEST_ADD_GROUP(Yuv444pToBgr);
    TEST_ADD_GROUP(Yuv422pToBgr);
    TEST_ADD_GROUP(Yuv420pToBgr);
    TEST_ADD_GROUP(Yuv444pToHsl);
    TEST_ADD_GROUP(Yuv444pToHsv);
    TEST_ADD_GROUP(Yuv444pToHue);
    TEST_ADD_GROUP(Yuv420pToHue);

    TEST_ADD_GROUP(Yuv444pToBgra);
    TEST_ADD_GROUP(Yuv422pToBgra);
    TEST_ADD_GROUP(Yuv420pToBgra);

    class Task
    {
        const Groups & _groups;
        std::thread _thread;
        volatile double _progress;
    public:
        static volatile bool s_stopped;

        Task(const Groups & groups, bool start)
            : _groups(groups)
            , _progress(0)
        {
            if(start)
                _thread = std::thread(&Task::Run, this);
        }

        ~Task()
        {
            if(_thread.joinable())
            {
                _thread.join();
            }
        }

        double Progress() const
        {
            return _progress;
        }

        void Run()
        {
            for(size_t i = 0; i < _groups.size() && !s_stopped; ++i)
            {
                _progress = double(i)/double(_groups.size());
                const Group & group = _groups[i];
                TEST_LOG_SS(Info, group.name << "AutoTest is started :"); 
                bool result = group.autoTest(); 
                TEST_LOG_SS(Info, group.name << "AutoTest - is finished " << (result ? "successfully." : "with errors!") << std::endl);
                if(!result) 
                { 
                    s_stopped = true;
                    TEST_LOG_SS(Error, "ERROR! TEST EXECUTION IS TERMINATED !" << std::endl); 
                    return;
                }
            }
            _progress = 1.0;
        }
    };
    volatile bool Task::s_stopped = false;
    typedef std::shared_ptr<Task> TaskPtr;
    typedef std::vector<TaskPtr> TaskPtrs;

    inline void Sleep(unsigned int miliseconds)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds));
    }

	struct Options
	{
        bool help;

		enum Mode
		{
			Auto,
			Create,
			Verify,
			Special,
		} mode;

		Strings filters;

		String output;

		size_t threads;

		Options(int argc, char* argv[])
			: mode(Auto)
			, threads(0)
            , help(false)
		{
			for (int i = 1; i < argc; ++i)
			{
				String arg = argv[i];
                if (arg.substr(0, 2) == "-h" || arg.substr(0, 2) == "-?")
                {
                    help = true;
                    break;
                }
                else if (arg.find("-m=") == 0)
				{
					switch (arg[3])
					{
					case 'a': mode = Auto; break;
					case 'c': mode = Create; break;
					case 'v': mode = Verify; break;
					case 's': mode = Special; break;
					default:
						TEST_LOG_SS(Error, "Unknown command line options: '" << arg << "'!" << std::endl);
						exit(1);
					}
				}
				else if (arg.find("-t=") == 0)
				{
#ifdef NDEBUG
					std::stringstream ss(arg.substr(3, arg.size() - 3));
					ss >> threads;
#endif
				}
				else if (arg.find("-f=") == 0)
				{
					filters.push_back(arg.substr(3, arg.size() - 3));
				}
				else if (arg.find("-o=") == 0)
				{
					output = arg.substr(3, arg.size() - 3);
				}
				else
				{
					TEST_LOG_SS(Error, "Unknown command line options: '" << arg << "'!" << std::endl);
					exit(1);
				}
			}
		}

		bool Required(const Group & group) const
		{
            if (mode == Auto && group.autoTest == NULL)
                return false;
            if ((mode == Create || mode == Verify) && group.dataTest == NULL)
                return false;
			if (mode == Special && group.specialTest == NULL)
                return false;
            if (filters.empty())
                return true;
            bool required = false;
            for (size_t i = 0; i < filters.size(); ++i)
            {
                if (group.name.find(filters[i]) != std::string::npos)
                {
                    required = true;
                    break;
                }
            }
            return required;
		}
	};

	int MakeAutoTests(const Groups & groups, const Options & options)
	{
		if (options.threads > 0)
		{
			TEST_LOG_SS(Info, "Test threads count = " << options.threads);

			Test::Log::s_log.SetLevel(Test::Log::Error);

			Test::TaskPtrs tasks;
			for (size_t i = 0; i < options.threads; ++i)
				tasks.push_back(Test::TaskPtr(new Test::Task(groups, true)));

			std::cout << std::endl;
			double progress;
			do
			{
				progress = 0;
				for (size_t i = 0; i < tasks.size(); ++i)
					progress += tasks[i]->Progress();
				progress /= double(tasks.size());
				std::cout << "\rTest progress = " << int(progress*100.0) << "%.";
				Test::Sleep(40);
			} while (progress < 1.0 && !Test::Task::s_stopped);
			std::cout << std::endl << std::endl;

			Test::Log::s_log.SetLevel(Test::Log::Info);
		}
		else
		{
			Test::Task task(groups, false);
			task.Run();
		}

		if (Test::Task::s_stopped)
			return 1;

		TEST_LOG_SS(Info, "ALL TESTS ARE FINISHED SUCCESSFULLY!" << std::endl);

#ifdef TEST_PERFORMANCE_TEST_ENABLE
		TEST_LOG_SS(Info, Test::PerformanceMeasurerStorage::s_storage.Report(true, true, false));
#endif
		return 0;
	}

	int MakeDataTests(const Groups & groups, const Options & options)
	{
		for (const Test::Group & group : groups)
		{
			bool create = options.mode == Test::Options::Create;
			TEST_LOG_SS(Info, group.name << "DataTest - data " << (create ? "creation" : "verification") << " is started :");
			bool result = group.dataTest(create);
			TEST_LOG_SS(Info, group.name << "DataTest - data " << (create ? "creation" : "verification") << " is finished " << (result ? "successfully." : "with errors!") << std::endl);
			if (!result)
			{
				TEST_LOG_SS(Error, "ERROR! TEST EXECUTION IS TERMINATED !" << std::endl);
				return 1;
			}
		}
		TEST_LOG_SS(Info, "ALL TESTS ARE FINISHED SUCCESSFULLY!" << std::endl);

		return 0;
	}

	int MakeSpecialTests(const Groups & groups, const Options & options)
	{
		for (const Test::Group & group : groups)
		{
			TEST_LOG_SS(Info, group.name << "SpecialTest - is started :");
			bool result = group.specialTest();
			TEST_LOG_SS(Info, group.name << "SpecialTest - data is finished " << (result ? "successfully." : "with errors!") << std::endl);
			if (!result)
			{
				TEST_LOG_SS(Error, "ERROR! TEST EXECUTION IS TERMINATED !" << std::endl);
				return 1;
			}
		}
		TEST_LOG_SS(Info, "ALL TESTS ARE FINISHED SUCCESSFULLY!" << std::endl);

		return 0;
	}

    int PrintHelp()
    {
        std::cout << "Test framework of Simd Library." << std::endl << std::endl;
        std::cout << "Using example:" << std::endl << std::endl;
        std::cout << "  ./Test -m=a -t=1 -f=Sobel -o=log.txt" << std::endl << std::endl;
        std::cout << "Where next parameters were used:" << std::endl << std::endl;
        std::cout << "-m=a       - a auto checking mode which includes performance testing" << std::endl; 
        std::cout << "             (only for library built in Release mode)." << std::endl;
        std::cout << "             In this case different implementations of each functions" << std::endl; 
        std::cout << "             will be compared between themselves " << std::endl;
        std::cout << "             (for example a scalar implementation and implementations" << std::endl; 
        std::cout << "             with using of different SIMD instructions such as SSE2, " << std::endl; 
        std::cout << "             AVX2, and other). Also it can be: " << std::endl;
        std::cout << "             -m=c - creation of test data for cross-platform testing), " << std::endl;
        std::cout << "             -m=v - cross - platform testing with using of early " << std::endl;
        std::cout << "             prepared test data)," << std::endl;
        std::cout << "             -m=s - running of special tests." << std::endl << std::endl;
        std::cout << "-t=1       - a number of used threads(every thread run all tests)" << std::endl;
        std::cout << "             for simulation of multi - thread loading." << std::endl << std::endl;
        std::cout << "-f=Sobel   - a filter. In current case will be tested only functions" << std::endl;
        std::cout << "             which contain word 'Sobel' in their names." << std::endl;
        std::cout << "             If you miss this parameter then full testing will be" << std::endl;
        std::cout << "             performed. You can use several filters - function name" << std::endl;
        std::cout << "             has to satisfy at least one of them. " << std::endl << std::endl;
        std::cout << "-o=log.txt - a file name with test report." << std::endl;
        std::cout << "             The test's report also will be output to console." << std::endl << std::endl;
        std::cout << "Also you can use parameter -h or -? to print this help message." << std::endl << std::endl;
        return 0;
    }
}

int main(int argc, char* argv[])
{
    Test::Options options(argc, argv);

    if (options.help)
        return Test::PrintHelp();

    if(!options.output.empty())
        Test::Log::s_log.SetLogFile(options.output);

    Test::Groups groups;
    for(const Test::Group & group : Test::g_groups)
        if(options.Required(group))
            groups.push_back(group);
    if(groups.empty())
    {
        std::stringstream ss;
        ss << "There are not any suitable tests for current filters: ";
        for (size_t i = 0; i < options.filters.size(); ++i)
            ss << "'" << options.filters[i] << "' ";
        ss << "!" << std::endl;
        TEST_LOG_SS(Error, ss.str()); 
        return 1;
    }

	switch (options.mode)
	{
	case Test::Options::Auto: 
		return Test::MakeAutoTests(groups, options);
	case Test::Options::Create:
	case Test::Options::Verify:
		return Test::MakeDataTests(groups, options);
	case Test::Options::Special:
		return Test::MakeSpecialTests(groups, options);
	default:
		return 0;
	}
}
