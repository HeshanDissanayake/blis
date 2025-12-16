# replace_blis_blocks.py
import argparse

def replace_blis_blocks(filename, replacements, output_file=None):
    """
    Replace BLIS blocksize identifiers in a file according to replacements dict.
    """
    if output_file is None:
        output_file = filename

    with open(filename, 'r') as f:
        content = f.read()

    for key, value in replacements.items():
        # replace whole identifiers
        content = content.replace(key, str(value))

    with open(output_file, 'w') as f:
        f.write(content)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Replace BLIS blocksize values in source file.")
    parser.add_argument("file", help="File to modify")
    parser.add_argument("--MR", type=int, required=True, help="Value for BLIS_MR")
    parser.add_argument("--NR", type=int, required=True, help="Value for BLIS_NR")
    parser.add_argument("--MC", type=int, required=True, help="Value for BLIS_MC")
    parser.add_argument("--KC", type=int, required=True, help="Value for BLIS_KC")
    parser.add_argument("--NC", type=int, required=True, help="Value for BLIS_NC")
    parser.add_argument("--out", default=None, help="Output file (default: overwrite input)")

    args = parser.parse_args()

    replacements = {
        "__MR__": args.MR,
        "__NR__": args.NR,
        "__MC__": args.MC,
        "__KC__": args.KC,
        "__NC__": args.NC
    }

    replace_blis_blocks(args.file, replacements, args.out)
    print(f"Updated {args.file} with new BLIS block sizes.")
