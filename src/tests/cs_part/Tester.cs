using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace cs_part
{
    internal class Tester
    {
        public int tests_count { get; private set; }
        public int success_tests_count { get; private set; }

        delegate decimal ArithmOperation(decimal left_operand, decimal right_operand);
        delegate int ComparisonOperation(decimal left_operand, decimal right_operand);
        delegate decimal OtherOperation(decimal operand);

        public Tester()
        {
            tests_count = 0;
            success_tests_count = 0;
        }

        public void ArithmTest()
        {
            BinaryReader lib_results;

            lib_results = new BinaryReader(new FileStream("data/arithm_results.dat", FileMode.Open));

            ArithmResultsComparison(Operations.Sum, ref lib_results);
            ArithmResultsComparison(Operations.Sub, ref lib_results);
            ArithmResultsComparison(Operations.Mul, ref lib_results);
            ArithmResultsComparison(Operations.Div, ref lib_results);
            ArithmResultsComparison(Operations.Mod, ref lib_results);

            lib_results.Close();
        }
        
        public void ComparisonTest()
        {
            BinaryReader lib_results;
            lib_results = new BinaryReader(new FileStream("data/cmp_results.dat", FileMode.Open));

            ComparisonResultsComparison(Operations.Less, ref lib_results);
            ComparisonResultsComparison(Operations.LessEq, ref lib_results);
            ComparisonResultsComparison(Operations.Greater, ref lib_results);
            ComparisonResultsComparison(Operations.GreaterEq, ref lib_results);
            ComparisonResultsComparison(Operations.Equal, ref lib_results);
            ComparisonResultsComparison(Operations.NotEqual, ref lib_results);

            lib_results.Close();
        }

        public void OtherTest()
        {
            BinaryReader lib_results;
            lib_results = new BinaryReader(new FileStream("data/other_results.dat", FileMode.Open));

            OtherResultsComparison(Operations.Negate, ref lib_results);
            OtherResultsComparison(Operations.Floor, ref lib_results);
            OtherResultsComparison(Operations.Truncate, ref lib_results);
            OtherResultsComparison(Operations.Round, ref lib_results);

            lib_results.Close();
        }

        private void ArithmResultsComparison(ArithmOperation op, ref BinaryReader br)
        {
            decimal left_operand, right_operand, cs_res, lib_res;
            BinaryReader input = new BinaryReader(new FileStream("data/input_values.dat", FileMode.Open));
            int count = input.ReadInt32();

            for (int i = 0; i < count / 2; i++)
            {
                left_operand = input.ReadDecimal();
                right_operand = input.ReadDecimal();
                cs_res = op(left_operand, right_operand);
                lib_res = br.ReadDecimal();
                if (cs_res == lib_res) this.success_tests_count++;
                else PrintError(cs_res, lib_res, op.Method.Name, left_operand, right_operand);

                this.tests_count++;
            }

            input.Close();
        }

        private void ComparisonResultsComparison(ComparisonOperation op, ref BinaryReader br)
        {
            decimal left_operand, right_operand;
            int cs_res, lib_res;
            BinaryReader input = new BinaryReader(new FileStream("data/input_values.dat", FileMode.Open));
            int count = input.ReadInt32();

            for (int i = 0; i < count / 2; i++)
            {
                left_operand = input.ReadDecimal();
                right_operand = input.ReadDecimal();
                cs_res = op(left_operand, right_operand);
                lib_res = br.ReadInt32();
                if (cs_res == lib_res) this.success_tests_count++;
                else PrintError(cs_res, lib_res, op.Method.Name, left_operand, right_operand);

                this.tests_count++;
            }

            input.Close();
        }

        private void OtherResultsComparison(OtherOperation op, ref BinaryReader br)
        {
            decimal operand, cs_res, lib_res;
            BinaryReader input = new BinaryReader(new FileStream("data/input_values.dat", FileMode.Open));
            int count = input.ReadInt32();

            for (int i = 0; i < count; i++)
            {
                operand = input.ReadDecimal();
                cs_res = op(operand);
                lib_res = br.ReadDecimal();
                if (cs_res == lib_res) this.success_tests_count++;
                else PrintError(cs_res, lib_res, op.Method.Name, operand);

                this.tests_count++;
            }

            input.Close();
        }

        private void PrintError(decimal cs_res, decimal lib_res, string operation, decimal operand)
        {
            Console.WriteLine(String.Format("=========== FAIL ==========="));
            Console.WriteLine(String.Format(" Operation {0}", operation));
            Console.WriteLine(String.Format(" Operand: {0}", operand));
            Console.WriteLine(String.Format(" C# result:  {0}", cs_res));
            Console.WriteLine(String.Format(" Lib result: {0}", lib_res));
            Console.WriteLine(String.Format("============================\n"));
        }
        private void PrintError(decimal cs_res, decimal lib_res, string operation,
                                decimal left_operand, decimal right_operand)
        {
            Console.WriteLine(String.Format("=========== FAIL ==========="));
            Console.WriteLine(String.Format(" Operation {0}", operation));
            Console.WriteLine(String.Format(" LOperand: {0}", left_operand));
            Console.WriteLine(String.Format(" ROperand: {0}", right_operand));
            Console.WriteLine(String.Format(" C# result:  {0}", cs_res));
            Console.WriteLine(String.Format(" Lib result: {0}", lib_res));
            Console.WriteLine(String.Format("============================\n"));
        }
    }
}
