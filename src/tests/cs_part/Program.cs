using System;
using System.Text;

namespace cs_part
{
    class Program
    {
        static void Main(string[] args)
        {
            Tester tester = new Tester();
            tester.ArithmTest();
            tester.ComparisonTest();
            tester.OtherTest();

            int total = tester.tests_count;
            int success = tester.success_tests_count;
            float percentage = (float)success / (float)total * 100;

            Console.WriteLine(String.Format("============ SUMMARY ============"));
            Console.WriteLine(String.Format(" Total number of tests: {0}", total.ToString()));
            Console.WriteLine(String.Format(" Number of success tests: {0}", success.ToString()));
            Console.WriteLine(String.Format(" Success percentage: {0:0.00}%", percentage.ToString()));
            Console.WriteLine(String.Format("================================="));
        }
    }
}
