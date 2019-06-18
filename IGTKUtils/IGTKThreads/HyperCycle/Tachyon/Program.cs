using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tachyon
{
    struct Payload
    {
        public int H { get; set; }
        public String Creator { get; set; }
        public bool Bypassed { get; set; }
    }

    class Node
    {
        public String Name { get; set; }
        public int Period { get; set; }
        private Dictionary<String, int> receivedPayloads = new Dictionary<string, int>();
        private List<Node> outputConnections = new List<Node>();
        private readonly object mutex = new object();
        public void Work(int h)
        {
            Payload outputPayload = new Payload();
            outputPayload.H = h;
            outputPayload.Creator = Name;

            Task t = Task.Factory.StartNew(() =>
            {
                bool receivedAll = false;
                while (!receivedAll)
                {
                    receivedAll = true;
                    lock (mutex)
                    {
                        foreach (var rp in receivedPayloads)
                        {
                            if (rp.Value != h)
                            {
                                receivedAll = false;
                            }
                        }
                    }
                }
            }
            );
               
            t.Wait();
            outputPayload.Bypassed = true;
            if (h % Period == 0)
            {
                System.Console.WriteLine(String.Format("{0} working at H = {1}. Inputs: {2}", Name, h,
                String.Join(" , ", receivedPayloads.Select(item => string.Format("[{0}:{1}]", item.Key, item.Value))))) ;
                outputPayload.Bypassed = false;
            }
            Send(outputPayload);
        }

        public void Connect(Node receiver)
        {
            outputConnections.Add(receiver);
            receiver.receivedPayloads[Name] = -1;
        }

        public void Receive(Payload payload)
        {
            lock (mutex)
            {
                receivedPayloads[payload.Creator] = payload.H;
            }
        }

        private void Send(Payload payload)
        {
            foreach (var output in outputConnections)
            {
                output.Receive(payload);
            }
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            // x:1 , y:2 ; a:3, b:2; o: 6
            /*
             * x -->a
             *     ^ \
             *    /   o
             *   /   /
             * y-->b
             */
            Node x = new Node { Name = "x", Period = 1 };
            Node y = new Node { Name = "y", Period = 2 };
            Node a = new Node { Name = "a", Period = 3 };
            Node b = new Node { Name = "b", Period = 2 };
            Node o = new Node { Name = "o", Period = 6 };
            var nodes = new List<Node>{ o, a, b, x, y };
            x.Connect(a);
            y.Connect(a); y.Connect(b);
            a.Connect(o);
            b.Connect(o);

            for (int h = 0; h < 10; ++h)
            {
                var tasks = new List<Task>();
                foreach (var n in nodes)
                {
                    tasks.Add(Task.Factory.StartNew(() =>
                    {
                        n.Work(h);
                    }));
                }
                Task.WhenAll(tasks).Wait(); ;
            }
        }
    }
}
