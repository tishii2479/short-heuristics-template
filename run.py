import multiprocessing
import pipes
import subprocess
from typing import Tuple

CASE = 100
TL = 6.0


def execute_case(seed):
    input_file_path = f"tools/in/{seed:04}.txt"
    output_file_path = f"tools/out/{seed:04}.txt"

    with open(input_file_path) as fin:
        with open(output_file_path, "w") as fout:
            subprocess.run(
                ["./a.out"],
                stdin=fin,
                stdout=fout,
                stderr=subprocess.PIPE,
                timeout=TL,
            )
            output = None
            # TODO: Read score
            # pipefile = f"tools/out/pipefile_{seed:04}"
            # with pipes.Template().open(pipefile, "w") as p:
            #     subprocess.run(
            #         ["tools/target/release/vis", input_file_path, output_file_path],
            #         stdout=p,
            #         timeout=TL,
            #     )
            # output = open(pipefile).read()
            assert output
    return seed, output


def main() -> None:
    scores = []
    count = 0
    total = 0

    subprocess.run("cargo build --release", shell=True)
    with multiprocessing.Pool(max(1, multiprocessing.cpu_count() - 2)) as pool:
        for seed, score in pool.imap_unordered(execute_case, range(CASE)):
            count += 1
            try:
                scores.append((int(score.split()[2]), f"{seed:04}"))
                total += scores[-1][0]
            except ValueError:
                print(seed, "ValueError", flush=True)
                print(score, flush=True)
                exit()
            except IndexError:
                print(seed, "IndexError", flush=True)
                print(f"error: {score}", flush=True)
                exit()

            print(
                f"case {seed:3}: (score: {scores[-1][0]:7}, current ave: {total / count:10.2f})",
                flush=True,
            )

    average_score = total / CASE
    print(f"average_score: {average_score}")


if __name__ == "__main__":
    main()
