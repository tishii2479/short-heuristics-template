import multiprocessing
import subprocess

total_cases = 100


def run_case(seed):
    proc = subprocess.run(
        f"./a.out < tools/in/{seed:04}.txt > out/{seed:04}.txt",
        shell=True,
        stderr=subprocess.PIPE,
    )
    stderr = proc.stderr.decode("utf8")
    for line in stderr.splitlines():
        if len(line) >= 6 and line[:6].lower() == "score:":
            score = int(line.split()[-1])
    return seed, score


def main():
    subprocess.run("g++-11 -std=c++17 main.cpp", shell=True)
    with multiprocessing.Pool(max(1, multiprocessing.cpu_count() - 2)) as pool:
        score_sum = 0
        for seed, score in pool.map(run_case, range(total_cases)):
            score_sum += score
            print(
                f"Seed: {seed}, Score: {score}, Current Average: {score_sum / (seed + 1)}"
            )

    print(f"Average {score_sum / total_cases}")


if __name__ == "__main__":
    main()
